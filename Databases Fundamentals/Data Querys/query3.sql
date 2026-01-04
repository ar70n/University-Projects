SELECT a.airport_code,
       Count(bp.flight_id) AS Pasajeros
FROM   airports_data a
       JOIN flights f
         ON f.arrival_airport = a.airport_code
       JOIN ticket_flights tf
         ON tf.flight_id = f.flight_id
       JOIN boarding_passes bp
         ON tf.ticket_no = bp.ticket_no
GROUP  BY a.airport_code
ORDER  BY pasajeros ASC;  
