import unittest
from unittest.mock import patch, MagicMock
import controller
import database
import os

class TestController(unittest.TestCase):
    @patch('controller.rule_engine')
    @patch('controller.mqttc')
    @patch('controller.database')
    def test_controller_rules(self, mock_database, mock_mqttc, mock_rule_engine):
        # 1. Usar una base de datos vacía
        mock_database.load.return_value = {
            "device_status_dict": {},
            "device_type_dict": {}
        }

        # 2. Mock del rule_engine
        mock_rule_engine.check_rules.return_value = "switch1 ON"

        # 3. Añadir un dispositivo switch (mock), y un sensor (mock)
        controller.device_status_dict['switch1'] = "OFF"
        controller.device_type_dict['switch1'] = "switch"
        controller.device_status_dict['sensor1'] = None
        controller.device_type_dict['sensor1'] = "sensor"

        # 4. Simular mensaje de sensor
        class DummyMessage:
            topic = "redes2/2301/06/sensor1/home/climate/sensor"
            payload = b"25"

        # 5. Llamar a on_message y comprobar que check_rules se llama
        controller.on_message(None, None, DummyMessage())
        mock_rule_engine.check_rules.assert_called_with('sensor1', '25')

        # 6. Simular mensaje de confirmación del switch1
        # Obtener el código de confirmación generado por controller
        confirmation_code = list(controller.awaiting_confirmation.values())[0]
        class DummyConfirmMessage:
            topic = "redes2/2301/06/switch1/home/climate/switch/confirm"
            payload = f"ON {confirmation_code}".encode()

        controller.on_message(None, None, DummyConfirmMessage())

        # 7. Comprobar que el estado del switch ha cambiado a ON tras la confirmación
        self.assertEqual(controller.device_status_dict['switch1'], "ON")

    def test_database_save_and_load(self):
        # Archivo temporal para la base de datos
        db_file = "test_db_controller.pkl"
        db_path = os.path.join(database.DB_ROOT, db_file)

        # 1. Establecer los diccionarios de controller con un dispositivo
        controller.device_status_dict.clear()
        controller.device_type_dict.clear()
        controller.device_status_dict["dev1"] = "ON"
        controller.device_type_dict["dev1"] = "switch"

        # 2. Guardar en la base de datos
        data = {
            "device_status_dict": controller.device_status_dict,
            "device_type_dict": controller.device_type_dict
        }
        database.save(data, db_file)

        # 3. Limpiar los diccionarios de controller
        controller.device_status_dict.clear()
        controller.device_type_dict.clear()

        # 4. Cargar desde la base de datos
        loaded = database.load(db_file)
        controller.device_status_dict = loaded["device_status_dict"]
        controller.device_type_dict = loaded["device_type_dict"]

        # 5. Comprobar que los datos se han cargado correctamente
        self.assertEqual(controller.device_status_dict, {"dev1": "ON"})
        self.assertEqual(controller.device_type_dict, {"dev1": "switch"})

        # 6. Eliminar el archivo generado
        if os.path.exists(db_path):
            os.remove(db_path)

if __name__ == '__main__':
    unittest.main()