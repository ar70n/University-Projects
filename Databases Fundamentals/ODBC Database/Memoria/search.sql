
WITH asientos_totales AS (
    SELECT 
        f.flight_id, 
        COUNT(s.seat_no) AS asientos_totales, 
        f.scheduled_departure 
    FROM 
        flights f 
        JOIN aircrafts_data ad ON ad.aircraft_code = f.aircraft_code 
        JOIN seats s ON s.aircraft_code = ad.aircraft_code 
    WHERE 
        DATE(f.scheduled_departure) >=  ?
        AND DATE(f.scheduled_departure) <=  ?
    GROUP BY 
        f.flight_id
),  
asientos_reservados AS (
    SELECT 
        f.flight_id, 
        COUNT(tf.ticket_no) AS asientos_reservados 
    FROM 
        ticket_flights tf 
        JOIN flights f ON tf.flight_id = f.flight_id 
    WHERE 
        DATE(f.scheduled_departure) >=  ?
        AND DATE(f.scheduled_departure) <= ? 
    GROUP BY 
        f.flight_id
), 
asientos_vacios AS (
    SELECT 
        AT.flight_id, 
        (AT.asientos_totales - COALESCE(ar.asientos_reservados,0)) AS vacios 
    FROM 
        asientos_totales AT 
        LEFT JOIN asientos_reservados ar ON ar.flight_id = AT.flight_id
),  
salidas AS (
    SELECT 
        f.flight_id, 
        f.departure_airport, 
        f.arrival_airport, 
        f.scheduled_departure, 
        f.scheduled_arrival, 
        AT.vacios AS asientos, 
        f.aircraft_code 
    FROM 
        flights f 
        JOIN asientos_vacios AT ON f.flight_id = AT.flight_id 
    WHERE 
        f.departure_airport = ?
        AND AT.vacios <> 0
	AND DATE(f.scheduled_departure)=?
),  
llegadas AS (
    SELECT 
        f.flight_id, 
        f.departure_airport, 
        f.arrival_airport, 
        f.scheduled_departure, 
        f.scheduled_arrival, 
        AT.vacios AS asientos, 
        f.aircraft_code 
    FROM 
        flights f 
        JOIN asientos_vacios AT ON f.flight_id = AT.flight_id 
    WHERE 
        f.arrival_airport = ?
        AND AT.vacios <> 0
)  
SELECT 
    first_flight_id, 
    fecha_salida_1, 
    fecha_llegada_2, 
    transbordos, 
    asientos_libres, 
    aircraft_code_1, 
    second_flight_id, 
    fecha_salida_2, 
    fecha_llegada_1, 
    aircraft_code_2 
FROM  
    (
        SELECT 
            s.flight_id AS first_flight_id, 
            s.scheduled_departure AS fecha_salida_1, 
            s.scheduled_arrival AS fecha_llegada_2, 
            s.departure_airport, 
            l.arrival_airport, 
            '1' AS transbordos, 
            CASE WHEN s.asientos >= l.asientos THEN l.asientos ELSE s.asientos END AS asientos_libres, 
            s.aircraft_code AS aircraft_code_1, 
            l.flight_id AS second_flight_id, 
            l.scheduled_departure AS fecha_salida_2, 
            l.scheduled_arrival AS fecha_llegada_1, 
            l.aircraft_code AS aircraft_code_2 
        FROM  
            salidas s 
            JOIN llegadas l ON s.arrival_airport = l.departure_airport 
        WHERE 
            s.scheduled_arrival < l.scheduled_departure 
            AND (l.scheduled_arrival - s.scheduled_departure) <= '24:00:00.000' 
        UNION 
        SELECT 
            s.flight_id AS first_flight_id, 
            s.scheduled_departure AS fecha_salida_1, 
            s.scheduled_arrival AS fecha_llegada_2, 
            s.departure_airport, 
            s.arrival_airport, 
            '0' AS transbordos, 
            s.asientos, 
            s.aircraft_code AS aircraft_code_1, 
            s.flight_id AS second_flight_id, 
            s.scheduled_departure AS fecha_salida_2, 
            s.scheduled_arrival AS fecha_llegada_1, 
            s.aircraft_code AS aircraft_code_2 
        FROM 
            salidas s 
        WHERE  
            s.arrival_airport = ?

    ) AS todos 
ORDER BY 
    (fecha_llegada_1 - fecha_salida_1) ASC;
