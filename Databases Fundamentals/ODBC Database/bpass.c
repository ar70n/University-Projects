/*
* Created by roberto on 3/5/21.
*/

#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "lbpass.h"
void    results_bpass(/*@unused@*/ char * bookID,
                       int * n_choices, char *** choices,
                       int max_length,
                       int max_rows)
/**here you need to do your query and fill the choices array of strings
*
* @param bookID  form field bookId
* @param n_choices fill this with the number of results
* @param choices fill this with the actual results
* @param max_length output win maximum width
* @param max_rows output win maximum number of rows
*/

{
    int i=0;
    int t=0;
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;

    /*DEBUG*/ 
    FILE *log=NULL;
    /*END DEBUG*/

    SQLCHAR flight_id[MAX_FIELD];
    SQLCHAR passenger_name[MAX_NAME];
    SQLCHAR scheduled_departure[MAX_FIELD];
    SQLCHAR seat_no[MAX_SEAT_NO];
    SQLCHAR final_array[MAX_FIELD];
    SQLCHAR space[MAX_SPACE] = " ";
    SQLLEN rows;

    SQLCHAR query1[] = "WITH vuelos AS (SELECT tf.flight_id,t.ticket_no,ROW_NUMBER() OVER (PARTITION BY tf.flight_id ORDER BY t.ticket_no) AS posicion FROM tickets t INNER JOIN ticket_flights tf ON t.ticket_no = tf.ticket_no WHERE t.book_ref = ? AND tf.flight_id NOT in (SELECT bp.flight_id FROM boarding_passes bp WHERE bp.ticket_no = t.ticket_no) GROUP BY tf.flight_id,t.ticket_no ORDER BY tf.flight_id,t.ticket_no),asientos AS (SELECT DISTINCT f.flight_id,s.seat_no FROM flights f INNER JOIN seats s ";
    SQLCHAR query2[] = "ON f.aircraft_code = s.aircraft_code INNER JOIN vuelos v ON f.flight_id = v.flight_id),asientos_ocupados AS (SELECT DISTINCT bp.flight_id,bp.seat_no FROM boarding_passes bp INNER JOIN vuelos v ON bp.flight_id = v.flight_id),asientos_vacios AS (SELECT DISTINCT a.flight_id,a.seat_no,row_number() OVER (PARTITION BY a.flight_id ORDER BY a.flight_id,a.seat_no) AS numero FROM asientos a WHERE a.flight_id not in (SELECT ao.flight_id FROM asientos_ocupados ao WHERE ao.seat_no = a.seat_no )) ";
    SQLCHAR query3[] = "SELECT t.passenger_name,v.flight_id,f.scheduled_departure,av.seat_no FROM asientos_vacios av,vuelos v,tickets t,flights f WHERE v.flight_id = av.flight_id AND v.posiciON = av.numero AND t.ticket_no = v.ticket_no AND f.flight_id = v.flight_id";
    SQLCHAR query4[] = "INSERT INTO boarding_passes (ticket_no,flight_id,boarding_no,seat_no) SELECT t.ticket_no,v.flight_id, COALESCE((SELECT MAX(bp.boarding_no) FROM boarding_passes bp WHERE bp.flight_id = v.flight_id), 0) + ROW_NUMBER() OVER (ORDER BY av.seat_no),av.seat_no FROM asientos_vacios av,vuelos v,tickets t,flights f,boarding_passes bp WHERE v.flight_id = av.flight_id AND v.posicion = av.numero AND t.ticket_no = v.ticket_no AND f.flight_id = v.flight_id GROUP BY t.ticket_no,v.flight_id,av.seat_no";

    SQLCHAR full_query[MAX_SQLCHAR]; 
    SQLCHAR insert[MAX_SQLCHAR];

    log = fopen("debug.log", "w");
    fprintf(log,"--LOG DE CONSULTA SEARCH--\n");
    fclose(log);

    if (bookID == NULL || n_choices == NULL || choices == NULL || max_length <= 0 || max_rows <= 0)
    {
        *n_choices=0;

        return;
    }

    strcpy((char*)full_query, (char*)query1);
    strcat((char*)full_query, (char*)query2); 
    strcat((char*)full_query, (char*)query3); 

    strcpy((char*)insert, (char*)query1);
    strcat((char*)insert, (char*)query2); 
    strcat((char*)insert, (char*)query4); 

    ret = odbc_connect(&env, &dbc);

    /*DEBUG*/
    log = fopen("debug.log", "a");
    if (SQL_SUCCEEDED(ret))
    {
        fprintf(log, "\nOperación exitosa. Conexion exitosa, code: %d\n", ret);
        fclose(log);

    }
    else
    {
        fprintf(log, "Error en la conexión con la base de datos, ret = %d\n", ret);
        fclose(log);
        *n_choices=0;
        return;
    }
    /*END DEBUG*/

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    
    SQLPrepare(stmt, full_query, SQL_NTS);
    /*SQLPrepare(stmt, (SQLCHAR*)"select * from flights where scheduled_departure > ? and scheduled_arrival < ? and departure_airport = ?  and arrival_airport=? limit 10", SQL_NTS);*/
    
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof((SQLCHAR*)bookID), 0, (SQLCHAR*)bookID, sizeof((SQLCHAR*)bookID), NULL);

    SQLExecute(stmt);
        
    SQLBindCol(stmt, 1, SQL_C_CHAR, passenger_name, sizeof(passenger_name), NULL);
    SQLBindCol(stmt, 2, SQL_C_CHAR, flight_id, sizeof(flight_id), NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, scheduled_departure, sizeof(scheduled_departure), NULL);
    SQLBindCol(stmt, 4, SQL_C_CHAR, seat_no, sizeof(seat_no), NULL);

    SQLRowCount(stmt, &rows);
    *n_choices = (int)rows;

    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)) && i < rows) {
    
        strcpy((char*)final_array, (char*)passenger_name);
        strcat((char*)final_array, (char*)space); 
        strcat((char*)final_array, (char*)flight_id); 
        strcat((char*)final_array, (char*)space);
        strcat((char*)final_array, (char*)scheduled_departure);
        strcat((char*)final_array, (char*)space);
        strcat((char*)final_array, (char*)seat_no);
        
        t = strlen((char*)final_array)+1;
        t = MIN(t, max_length);
        strncpy((*choices)[i], (char*)final_array, t);
        i++;
    }

    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLPrepare(stmt, insert, SQL_NTS);
    
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof((SQLCHAR*)bookID), 0, (SQLCHAR*)bookID, sizeof((SQLCHAR*)bookID), NULL);

    SQLExecute(stmt);

    SQLCloseCursor(stmt);

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
}

