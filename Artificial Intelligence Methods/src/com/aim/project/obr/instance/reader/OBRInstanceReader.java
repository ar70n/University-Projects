package com.aim.project.obr.instance.reader;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Random;

import com.aim.project.obr.instance.Location;
import com.aim.project.obr.instance.OpenTopBusRoutingInstance;
import com.aim.project.obr.interfaces.OBRInstanceInterface;
import com.aim.project.obr.interfaces.OBRInstanceReaderInterface;

/**
 * @author Warren G Jackson
 * @since 1.0.0 (15/03/2026)
 */
public class OBRInstanceReader implements OBRInstanceReaderInterface {
	//private String name;
	//private String comment;
	
	@Override
	public OBRInstanceInterface readOBRInstanceFile(Path oPath, Random oRandom) {
		
		try (BufferedReader br = Files.newBufferedReader(oPath, StandardCharsets.UTF_8)){
			Location bus_depot = null;
			int x, y, x_d = 0, y_d = 0;
			String line = br.readLine().trim();
            //name = line.substring("NAME :".length()).trim();

            line = br.readLine().trim();
            //comment = line.substring("COMMENT :".length()).trim();
            
            br.readLine(); //BUS_DEPOT_LOCATION
            
            line = br.readLine().trim();
            String[] parts = line.split("\\s+");
            if (parts.length >= 2) {
                x_d = Integer.parseInt(parts[0]);
                y_d = Integer.parseInt(parts[1]);
            }
            
            br.readLine(); //POINTS_OF_INTEREST
            
            ArrayList<Location> list = new ArrayList<>();
            while ((line = br.readLine()) != null) {
            	line = line.trim();
                if (line.equals("EOF")) {
            		break;
            	}
            	parts = line.split("\\s+");
                if (parts.length >= 2) {
                    x = Integer.parseInt(parts[0]);
                    y = Integer.parseInt(parts[1]); 
                    list.add(new Location(x,y));
                }
            }
            Location[] aoLocations = list.toArray(new Location[list.size()]);
			bus_depot = new Location(x_d,y_d); //We do this because we want the location with ID 0 to be the first PoI instead of the BD

            //Segun el getter the OBRInstanceInterface creo que hay que incluir el bus_depot en el numero de locations
			return new OpenTopBusRoutingInstance(aoLocations.length + 1, aoLocations, bus_depot, oRandom);
			
		} catch (IOException e) {
			e.printStackTrace();
		}
        return null;
    }
}
