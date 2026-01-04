/*
 * Created by roberto on 3/5/21.
 */

#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "search.h"

int results_search(char *from, char *to, char *date,
                    int *n_choices, char ***choices, char ***message,
                    int max_length,
                    int max_rows)
/**here you need to do your query and fill the choices array of strings
 *
 * @param from form field from
 * @param to form field to
 * @param date form field date
 * @param n_choices fill this with the number of results
 * @param choices fill this with the actual results
 * @param max_length output win maximum width
 * @param max_rows output win maximum number of rows
 */
{
    int i = 0;
    int t = 0;
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLRETURN status, status2;

    SQL_TIMESTAMP_STRUCT fecha1;
    SQL_TIMESTAMP_STRUCT fecha2;
    unsigned short int year;
    unsigned short int month;
    unsigned short int day;

    SQLLEN num_filas;
    /*DEBUG*/
    FILE *log = NULL;
    /*END DEBUG*/

    SQLCHAR first_flight_id[512];
    SQLCHAR fecha_salida_1[512];
    SQLCHAR fecha_llegada_1[512];
    SQLCHAR transbordos[64];
    SQLCHAR asientos_libres[512];
    SQLCHAR aircraft_code_1[512];
    SQLCHAR second_flight_id[512];
    SQLCHAR fecha_salida_2[512];
    SQLCHAR fecha_llegada_2[512];
    SQLCHAR aircraft_code_2[512];

    SQLCHAR final_array[8192];
    SQLCHAR final_array2[8192];

    SQLCHAR space[2] = " ";
    SQLCHAR consulta_completa[4096];

    SQLCHAR parte1[] = "WITH asientos_totales AS (SELECT f.flight_id, COUNT(s.seat_no) AS asientos_totales, f.scheduled_departure FROM flights f JOIN aircrafts_data ad ON ad.aircraft_code = f.aircraft_code JOIN seats s ON s.aircraft_code = ad.aircraft_code WHERE DATE(f.scheduled_departure) >= ? AND DATE(f.scheduled_departure) <= ? GROUP BY f.flight_id), asientos_reservados AS (SELECT f.flight_id, COUNT(tf.ticket_no) AS asientos_reservados FROM ticket_flights tf JOIN flights f ON tf.flight_id = f.flight_id WHERE ";
    SQLCHAR parte2[] = "DATE(f.scheduled_departure) >= ? AND DATE(f.scheduled_departure) <= ? GROUP BY f.flight_id), asientos_vacios AS (SELECT AT.flight_id, (AT.asientos_totales - COALESCE(ar.asientos_reservados, 0)) AS vacios FROM asientos_totales AT LEFT JOIN asientos_reservados ar ON ar.flight_id = AT.flight_id), salidas AS (SELECT f.flight_id, f.departure_airport, f.arrival_airport, f.scheduled_departure, f.scheduled_arrival, AT.vacios AS asientos, f.aircraft_code FROM flights f JOIN asientos_vacios AT ON f.flight_id = ";
    SQLCHAR parte3[] = "AT.flight_id WHERE f.departure_airport = ? AND AT.vacios <> 0 AND DATE(f.scheduled_departure) = ?), llegadas AS (SELECT f.flight_id, f.departure_airport, f.arrival_airport, f.scheduled_departure, f.scheduled_arrival, AT.vacios AS asientos, f.aircraft_code FROM flights f JOIN asientos_vacios AT ON f.flight_id = AT.flight_id WHERE f.arrival_airport = ? AND AT.vacios <> 0) SELECT first_flight_id, fecha_salida_1, fecha_llegada_2, transbordos, asientos_libres, aircraft_code_1, ";
    SQLCHAR parte4[] = "second_flight_id, fecha_salida_2, fecha_llegada_1, aircraft_code_2 FROM (SELECT s.flight_id AS first_flight_id, s.scheduled_departure AS fecha_salida_1, s.scheduled_arrival AS fecha_llegada_2, s.departure_airport, l.arrival_airport, '1' AS transbordos, CASE WHEN s.asientos >= l.asientos THEN l.asientos ELSE s.asientos END AS asientos_libres, ";
    SQLCHAR parte5[] = "s.aircraft_code AS aircraft_code_1, l.flight_id AS second_flight_id, l.scheduled_departure AS fecha_salida_2, l.scheduled_arrival AS fecha_llegada_1, l.aircraft_code AS aircraft_code_2 FROM salidas s JOIN llegadas l ON s.arrival_airport = l.departure_airport WHERE s.scheduled_arrival < l.scheduled_departure AND (l.scheduled_arrival - s.scheduled_departure) <= '24:00:00.000' UNION SELECT s.flight_id AS first_flight_id, s.scheduled_departure AS fecha_salida_1, s.scheduled_arrival AS fecha_llegada_2, ";
    SQLCHAR parte6[] = "s.departure_airport, s.arrival_airport, '0' AS transbordos, s.asientos, s.aircraft_code AS aircraft_code_1, s.flight_id AS second_flight_id, s.scheduled_departure AS fecha_salida_2, s.scheduled_arrival AS fecha_llegada_1, s.aircraft_code AS aircraft_code_2 FROM salidas s WHERE s.arrival_airport = ?) AS todos ORDER BY (fecha_llegada_1 - fecha_salida_1) ASC;";


    log = fopen("debug.log", "w");
    fprintf(log,"--LOG DE CONSULTA SEARCH--\n");
    fclose(log);


    if (from == NULL || to == NULL || date == NULL || n_choices == NULL || choices == NULL || message == NULL || max_length <= 0 || max_rows <= 0)
    {
        *n_choices=0;

        return -1;
    }

    strcpy((char *)consulta_completa, (char *)parte1);
    strcat((char *)consulta_completa, (char *)parte2);
    strcat((char *)consulta_completa, (char *)parte3);
    strcat((char *)consulta_completa, (char *)parte4);
    strcat((char *)consulta_completa, (char *)parte5);
    strcat((char *)consulta_completa, (char *)parte6);

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
        return -2;
    }

    /*END DEBUG*/

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLPrepare(stmt, consulta_completa, SQL_NTS);

    sscanf(date, "%4hu_%2hu_%2hu", &year, &month, &day);
    fecha1.year = year;
    fecha1.month = month;
    fecha1.day = day;
    fecha1.hour = 0;
    fecha1.minute = 0;
    fecha1.second = 0;
    fecha1.fraction = 0;

    fecha2.year = fecha1.year;
    fecha2.month = fecha1.month;
    fecha2.day = fecha1.day + 1;
    fecha2.hour = 0;
    fecha2.minute = 0;
    fecha2.second = 0;
    fecha2.fraction = 0;

    /*Aqui a poner tantas llamadas a funcion como interrogaciones y en orden!*/
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 0, 0, &fecha1, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 0, 0, &fecha2, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 0, 0, &fecha1, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 0, 0, &fecha2, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof((SQLCHAR *)from), 0, (SQLCHAR *)from, sizeof((SQLCHAR *)from), NULL);
    SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 0, 0, &fecha1, 0, NULL);
    SQLBindParameter(stmt, 7, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof((SQLCHAR *)to), 0, (SQLCHAR *)to, sizeof((SQLCHAR *)to), NULL);
    SQLBindParameter(stmt, 8, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof((SQLCHAR *)to), 0, (SQLCHAR *)to, sizeof((SQLCHAR *)to), NULL);

    status = SQLExecute(stmt);

    /*DEBUG*/
    log = fopen("debug.log", "a");
    if (SQL_SUCCEEDED(status))
    {
        fprintf(log, "\nOperación exitosa. ejecución exitosa, code: %d\n", ret);
    }
    else
    {
        fprintf(log, "Error en la operación\n");
    }
    fprintf(log, "From: %s, To: %s, Date: %s\n"
                 "Ret connection: %d,\n"
                 "Ret execution: %d,\n"
                 "fecha1 year: %d, month: %d, day: %d,\n"
                 "Query:\n%s",
            from, to, date, ret, status, fecha1.year, fecha1.month, fecha1.day,
            consulta_completa);

    if (status != SQL_SUCCESS)
    {
        SQLSMALLINT recNumber = 1;
        SQLCHAR sqlState[6];
        SQLINTEGER nativeError;
        SQLCHAR messageText[SQL_MAX_MESSAGE_LENGTH];
        SQLSMALLINT textLength;

        while (SQLGetDiagRec(SQL_HANDLE_STMT, stmt, recNumber, sqlState, &nativeError, messageText, sizeof(messageText), &textLength) == SQL_SUCCESS)
        {
            fprintf(log, "SQLSTATE: %s\n", sqlState);
            fprintf(log, "Native Error: %ld\n", (long)nativeError);
            fprintf(log, "Message: %s\n", messageText);
            recNumber++;
        }
    
    }

    fclose(log);
    if (!SQL_SUCCEEDED(status)) {
    
        *n_choices=0;
        return -1;
    }
    /*END DEBUG*/
    /*Para cada atributo de salida asociamos una variable*/
    SQLBindCol(stmt, 1, SQL_C_CHAR, first_flight_id, sizeof(first_flight_id), NULL);
    SQLBindCol(stmt, 2, SQL_C_CHAR, fecha_salida_1, sizeof(fecha_salida_1), NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, fecha_llegada_2, sizeof(fecha_llegada_2), NULL);
    SQLBindCol(stmt, 4, SQL_C_CHAR, transbordos, sizeof(transbordos), NULL);
    SQLBindCol(stmt, 5, SQL_C_CHAR, asientos_libres, sizeof(asientos_libres), NULL);
    SQLBindCol(stmt, 6, SQL_C_CHAR, aircraft_code_1, sizeof(aircraft_code_1), NULL);
    SQLBindCol(stmt, 7, SQL_C_CHAR, second_flight_id, sizeof(second_flight_id), NULL);
    SQLBindCol(stmt, 8, SQL_C_CHAR, fecha_salida_2, sizeof(fecha_salida_2), NULL);
    SQLBindCol(stmt, 9, SQL_C_CHAR, fecha_llegada_1, sizeof(fecha_llegada_1), NULL);
    SQLBindCol(stmt, 10, SQL_C_CHAR, aircraft_code_2, sizeof(aircraft_code_2), NULL);

    status2 = SQLRowCount(stmt, &num_filas);

    *(n_choices) = (int)num_filas;
    max_rows = MIN(*n_choices, max_rows);

    /*DEBUG*/
    log = fopen("debug.log", "a");
    if (status == SQL_SUCCESS || status2 == SQL_SUCCESS_WITH_INFO)
    {
        fprintf(log, "\nOperación exitosa. Filas afectadas: %ld\n"
                     "max_rows = %d",
                num_filas, max_rows);
                    fclose(log);

    }
    else
    {
        fprintf(log, "Error en la operación\n");
        fclose(log);
        *n_choices=0;
        return -1;

    }
    /*END DEBUG*/

    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)) && i < num_filas)
    {

        log = fopen("debug.log", "a");
        fprintf(log, "\nEntra en el bucle, ret = %d\n", ret);
        fclose(log);

        strcpy((char *)final_array, (char *)first_flight_id);
        strcat((char *)final_array, (char *)space);
        strcat((char *)final_array, (char *)fecha_salida_1);
        strcat((char *)final_array, (char *)space);
        strcat((char *)final_array, (char *)fecha_llegada_1);
        strcat((char *)final_array, (char *)space);
        strcat((char *)final_array, (char *)transbordos);
        strcat((char *)final_array, (char *)space);
        strcat((char *)final_array, (char *)asientos_libres);

        if (transbordos[0] == '0')
        {

            strcpy((char *)final_array2, (char *)first_flight_id);
            strcat((char *)final_array2, (char *)space);
            strcat((char *)final_array2, (char *)fecha_salida_1);
            strcat((char *)final_array2, (char *)space);
            strcat((char *)final_array2, (char *)fecha_llegada_1);
            strcat((char *)final_array2, (char *)space);
            strcat((char *)final_array2, (char *)aircraft_code_1);
        }
        else
        {
            strcpy((char *)final_array2, (char *)first_flight_id);
            strcat((char *)final_array2, (char *)space);
            strcat((char *)final_array2, (char *)fecha_salida_1);
            strcat((char *)final_array2, (char *)space);
            strcat((char *)final_array2, (char *)fecha_llegada_2);
            strcat((char *)final_array2, (char *)space);
            strcat((char *)final_array2, (char *)aircraft_code_1);
            strcat((char *)final_array2, (char *)space);
            strcat((char *)final_array2, (char *)second_flight_id);
            strcat((char *)final_array2, (char *)space);
            strcat((char *)final_array2, (char *)fecha_salida_2);
            strcat((char *)final_array2, (char *)space);
            strcat((char *)final_array2, (char *)fecha_llegada_1);
            strcat((char *)final_array2, (char *)space);
            strcat((char *)final_array2, (char *)aircraft_code_2);
        }
        /*DEBUG*/
        log = fopen("debug.log", "a");
        fprintf(log, "\n>[i:%d] ret: %d,"
                     "\nfinal array: %s",
                i, ret, final_array);

        fclose(log);

        /*END DEBUG*/

        t = strlen((char *)final_array) + 1;
        t = MIN(t, max_length);
        strncpy((*choices)[i], (char *)final_array, t);

        t = strlen((char *)final_array2) + 1;
        t = MIN(t, max_length);
        strncpy((*message)[i], (char *)final_array2, t);

        i++;
    }
    /*DEBUG*/

    log = fopen("debug.log", "a");
    if (SQL_SUCCEEDED(ret))
    {
        fprintf(log, "\nOperación exitosa. SQLFetch(stmt), code: %d\n", ret);
            fclose(log);

    }
    else
    {
        fprintf(log, "\nError en la operación SQLFetch(stmt) stmt: %p, codigo: %d\n", stmt, ret);

        SQLSMALLINT recNumber = 1;
        SQLCHAR sqlState[6];
        SQLINTEGER nativeError;
        SQLCHAR messageText[SQL_MAX_MESSAGE_LENGTH];
        SQLSMALLINT textLength;

        while (SQLGetDiagRec(SQL_HANDLE_STMT, stmt, recNumber, sqlState, &nativeError, messageText, sizeof(messageText), &textLength) == SQL_SUCCESS)
        {
            fprintf(log, "\nSQLSTATE: %s\n", sqlState);
            fprintf(log, "Native Error: %ld\n", (long)nativeError);
            fprintf(log, "Message: %s\n", messageText);
            recNumber++;
        }
        
            fclose(log);
          
    }
    /*END DEBUG*/

    SQLCloseCursor(stmt);

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (SQL_SUCCEEDED(ret)){
        return 0;
    }
    else 
    {
        log = fopen("debug.log", "a");
        fprintf(log,"\nError en la desconexión, ret = %d",ret);
        fclose(log);
        *n_choices=0;
        return -2;
    }
    
}
