#Se importan las clases necesarias para crear el servidor (httpserver) y manejar las solicitudes (simplehttprequesthandler)
from http.server import HTTPServer, SimpleHTTPRequestHandler    
import time #Este módulo es para trabajar con la fecha y hora actual

#Definición de host y port
HOST = "SU DIRECCIÓN IP"
PORT = "SU PUERTO" #TENGA EN CUENTA QUE EL PUERTO ES UN ENTERO NO UN STRING, POR LO QUE NO DEBE LLEVAR COMILLAS


class MiHTTP(SimpleHTTPRequestHandler):
#El método do_GET maneja las soliccitudes GET 
    def do_GET(self):

        self.send_response(200) #Envía un código de estado HTTP 200, que indica que la solicitud fue exitosa.
        self.send_header("Content-type", "text/html") #Indica que el contenido de la respuesta será de tipo HTML.
        self.end_headers() #Finaliza el encabezado HTTP.

        self.wfile.write(bytes("<html><body><h1>HELLO WORLD!</h1</body></html>","utf-8")) #nvía al cliente un mensaje HTML

    #El metodo do_POST manera las solicitudes post
    def do_POST(self):
        self.send_response(200)
        self.send_header("Content-type", "application/json") #Establece que la respuesta será en formato JSON.
        self.end_headers()

        date = time.strftime("%Y-%m-%d %H:%M:%S",time.localtime(time.time())) #Envía al cliente un JSON con la fecha y hora actual
        self.wfile.write(bytes('{"time": "' + date + '"}', "utf-8"))


server = HTTPServer((HOST, PORT), MiHTTP)
print("Server now running...")
server.serve_forever()
server.serve_close()

print("server stopped")
