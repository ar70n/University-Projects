WITH asientos_totales
     AS (SELECT f.flight_id,
                Count(s.seat_no) AS asientos_totales
         FROM   flights f
                JOIN aircrafts_data ad
                  ON ad.aircraft_code = f.aircraft_code
                JOIN seats s
                  ON s.aircraft_code = ad.aircraft_code
         GROUP  BY f.flight_id),
     asientos_reservados
     AS (SELECT f.flight_id,
                Count(tf.ticket_no) AS asientos_reservados
         FROM   ticket_flights tf
                FULL JOIN flights f
                       ON f.flight_id = tf.flight_id
         GROUP  BY f.flight_id),
     asientos_vacios
     AS (SELECT at.flight_id,
                ( at.asientos_totales - ar.asientos_reservados ) AS vacios
         FROM   asientos_totales at
                FULL JOIN asientos_reservados ar
                       ON ar.flight_id = at.flight_id)
SELECT av.flight_id,
       av.vacios
FROM   asientos_vacios av
WHERE  av.vacios = (SELECT Max(av.vacios)
                    FROM   asientos_vacios av);

