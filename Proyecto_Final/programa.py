import tkinter as tk
from tkinter import ttk
import serial

# Función que convierte al formato RGB
def a_rgb(rgb):
    return "#%02x%02x%02x" % rgb  

# Creación de la ventana principal
ventana = tk.Tk()

# Conexión serial con el Arduino
ser = serial.Serial(write_timeout=None)
ser.baudrate = 9600
ser.port = 'COM4'
ser.open()

# Elemento que cambiará de color según
# lo que el Arduino mande
fondo = tk.Label(bg="black")
fondo.place(x=780, y=90, width=300, height=300)

# Elemento que muestra el valor hexadecimal
# del color recibido
rgb_label = tk.Label(text="Ningún color recibido")
rgb_label.place(x=820, y=390, width=223, height=49)

# Texto informativo
texto_str = ("Proyecto:\nIdentificación de colores de objetos\n"
			 "\nFuncionamiento:\nSimplemente pon a la vista "
			 "del sensor el objeto,\npresiona el boton ¡Y listo!\n"
			 "el programa mostrara el color y su código hexadecimal")
texto = tk.Label(text=texto_str, justify=tk.LEFT)
texto.place(x=80, y=60, width=600, height=600)

# Función que realiza que pide el color al Arduino,
# lo procesa y lo muestra
def cambio_color():
	ser.write(str.encode("a"))
	cadena = ser.readline().decode("utf-8").strip().split(",")
	valor_rgb = a_rgb((int(cadena[0]), int(cadena[1]), int(cadena[2])))
	fondo.configure(bg=valor_rgb)
	rgb_label["text"] = f'Hexadecimal: {valor_rgb}'

# Botón para detectar el color
boton = ttk.Button(text="Detectar color", command=cambio_color)
boton.place(x=800, y=540, width=260, height=82)

# Inicio de la ventana principal
ventana.title("Proyecto")
ventana.geometry("1280x720")
ventana.resizable(width=False, height=False)
ventana.mainloop()
