# Version 1.0
# Por lo general no se requiere modificar el fichero

export PGDATABASE:=flight
export PGUSER :=postgres
export PGPASSWORD :=7240
export PGCLIENTENCODING:=UTF8
export PGHOST:=localhost

DBNAME =$(PGDATABASE)
PSQL = psql
CREATEDB = createdb
DROPDB = dropdb --if-exists
PG_DUMP = pg_dump
PG_RESTORE = pg_restore

all: dropdb createdb restore shell
mycomando:
	@echo aqui va una descripcion
	@cat myfichero.sql | psql mibasededatos
createdb:
	@echo Creando BBDD
	@$(CREATEDB)
dropdb:
	@echo Eliminando BBDD
	@$(DROPDB) $(DBNAME)
	rm -f *.log
dump:
	@echo creando dumpfile
	@$(PG_DUMP) > $(DBNAME).sql
restore:
	@echo restore data base
	@cat $(DBNAME).sql | $(PSQL)  
psql: shell
shell:
	@echo create psql shell
	@$(PSQL)  

allqueries: query1 query2 query3 query4 query5 query6
	@cat query?.log > all_queries.log

query1:
	@echo query-1: "No fuimos capaces de hacerla" | tee query1.log
	@cat query1.sql | $(PSQL) | tee -a query1.log
query2:
	@echo query-2: "Para hacer esta consulta hicimos una tabla con el numero de reserva, el monto total de la reserva y una tercera columna que se corresponde con la suma del monto de todos los billetes de una reserva. Hicimos esto para todas las reservas." | tee query2.log
	@cat query2.sql | $(PSQL) | tee -a query2.log
query3:
	@echo query3: "Para esta consulta hicimos una tabla con el codigo de todos los aeropuertos y una segunda columna (Pasajeros) que cuenta el numero de flight_id en boarding_passes por cada aeropuerto de destino" | tee query3.log
	@cat query3.sql | $(PSQL) | tee -a query3.log
query4:
	@echo query4: "Para esta consulta calculamos el numero de asientos totales en cada avión asociado a cada flight_id, después calculamos el numero de asientos reservados contando los numeros de ticket asociados a un flight_id, lo restamos y mostramos el resultado mas alto en una tabla junto con el flight_id" | tee query4.log
	@cat query4.sql | $(PSQL) | tee -a query4.log
query5:
	@echo query5: "Para esta consulta creamos dos subtablas: la primera reúne las reservas con tarjetas de embarque, y la segunda subtabla reúne la totalidad de las reservas. Juntamos las dos subtablas tal que las tuplas de la primera subtabla no tengan ninguna tarjeta de embarque" | tee query5.log
	@cat query5.sql | $(PSQL) | tee -a query5.log
query6:
	@echo query6: "Para esta consulta hicimos una tabla con el numero de vuelo y una columna con el promedio de retraso de todos los vuelos asociados a un numero de vuelo y mostramos el resultado mas alto" | tee query6.log
	@cat query6.sql | $(PSQL) | tee -a query6.log

