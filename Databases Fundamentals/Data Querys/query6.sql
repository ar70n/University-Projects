WITH retraso_medio
     AS (SELECT f.flight_no,
                Avg(f.actual_arrival - f.scheduled_arrival) AS retraso_medio
         FROM   flights f
         GROUP  BY f.flight_no
         ORDER  BY retraso_medio DESC)
SELECT rm.flight_no,
       rm.retraso_medio
FROM   retraso_medio rm
WHERE  rm.retraso_medio = (SELECT Max(rm.retraso_medio)
                           FROM   retraso_medio rm);

