WITH vuelos AS
  (SELECT tf.flight_id,
          t.ticket_no,
          ROW_NUMBER() OVER (PARTITION BY tf.flight_id
                             ORDER BY t.ticket_no) AS posicion
   FROM tickets t
   INNER JOIN ticket_flights tf ON t.ticket_no = tf.ticket_no
   WHERE t.book_ref = ?
     AND tf.flight_id NOT in
       (SELECT bp.flight_id
        FROM boarding_passes bp
        WHERE bp.ticket_no = t.ticket_no)
   GROUP BY tf.flight_id,
            t.ticket_no
   ORDER BY tf.flight_id,
            t.ticket_no),
     asientos AS
  (SELECT DISTINCT f.flight_id,
                   s.seat_no
   FROM flights f
   INNER JOIN seats s ON f.aircraft_code = s.aircraft_code
   INNER JOIN vuelos v ON f.flight_id = v.flight_id),
     asientos_ocupados AS
  (SELECT DISTINCT bp.flight_id,
                   bp.seat_no
   FROM boarding_passes bp
   INNER JOIN vuelos v ON bp.flight_id = v.flight_id),
     asientos_vacios AS
  (SELECT DISTINCT a.flight_id,
                   a.seat_no,
                   row_number() OVER (PARTITION BY a.flight_id
                                      ORDER BY a.flight_id,
                                               a.seat_no) AS numero
   FROM asientos a
   WHERE a.flight_id not in
       (SELECT ao.flight_id
        FROM asientos_ocupados ao
        WHERE ao.seat_no = a.seat_no ) )
SELECT t.passenger_name,
       v.flight_id,
       f.scheduled_departure,
       av.seat_no
FROM asientos_vacios av,
     vuelos v,
     tickets t,
     flights f
WHERE v.flight_id = av.flight_id
  AND v.posiciON = av.numero
  AND t.ticket_no = v.ticket_no
  AND f.flight_id = v.flight_id
  INSERT INTO boarding_passes (ticket_no, flight_id, boarding_no, seat_no)
SELECT t.ticket_no,
       v.flight_id,
       COALESCE(
                  (SELECT MAX(bp.boarding_no)
                   FROM boarding_passes bp
                   WHERE bp.flight_id = v.flight_id), 0) + ROW_NUMBER() OVER (
                                                                              ORDER BY av.seat_no) , av.seat_no
FROM asientos_vacios av,
     vuelos v,
     tickets t,
     flights f,
     boarding_passes bp
WHERE v.flight_id = av.flight_id
  AND v.posicion = av.numero
  AND t.ticket_no = v.ticket_no
  AND f.flight_id = v.flight_id
GROUP BY t.ticket_no,
         v.flight_id,
         av.seat_no