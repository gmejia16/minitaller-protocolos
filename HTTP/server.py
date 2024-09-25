#Se importan las clases necesarias para crear el servidor (httpserver) y manejar las solicitudes (simplehttprequesthandler)
from http.server import HTTPServer, SimpleHTTPRequestHandler    
import time

#Definición de host y port
HOST = "SU DIRECCIÓN IP"
PORT = "SU PUERTO" #TENGA EN CUENTA QUE EL PUERTO ES UN ENTERO NO UN STRING, POR LO QUE NO DEBE LLEVAR COMILLAS


class MiHTTP(SimpleHTTPRequestHandler):

    def do_GET(self):

        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()

        self.wfile.write(bytes("<html><body><h1>HELLO WORLD!</h1</body></html>","utf-8"))

    def do_POST(self):
        self.send_response(200)
        self.send_header("Content-type", "application/json")
        self.end_headers()

        date = time.strftime("%Y-%m-%d %H:%M:%S",time.localtime(time.time()))
        self.wfile.write(bytes('{"time": "' + date + '"}', "utf-8"))


server = HTTPServer((HOST, PORT), MiHTTP)
print("Server now running...")
server.serve_forever()
server.serve_close()

print("server stopped")
