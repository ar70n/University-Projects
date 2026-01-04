WITH reservas_totales
     AS (SELECT tf.ticket_no,
                tf.flight_id,
                t.book_ref
         FROM   ticket_flights tf,
                tickets t
         WHERE  tf.ticket_no = t.ticket_no),
     reservas_sin_tarjetas_de_embarque
     AS (SELECT tf.flight_id,
                t.book_ref,
                tf.ticket_no
         FROM   boarding_passes bp,
                tickets t,
                ticket_flights tf
         WHERE  bp.ticket_no = t.ticket_no
                AND t.ticket_no = tf.ticket_no
                AND bp.flight_id = tf.flight_id)
SELECT DISTINCT rt.book_ref,
                rt.flight_id
FROM   reservas_totales rt
       LEFT JOIN reservas_sin_tarjetas_de_embarque rstde
              ON rt.book_ref = rstde.book_ref
                 AND rt.flight_id = rstde.flight_id
                 AND rt.ticket_no = rstde.ticket_no
WHERE  rstde.book_ref IS NULL
        OR rstde.ticket_no IS NULL
ORDER  BY rt.book_ref,
          rt.flight_id; 

