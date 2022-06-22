import tkinter as tk
from tkinter import ttk
import serial

def a_rgb(rgb):
    return "#%02x%02x%02x" % rgb  

ventana = tk.Tk()
ser = serial.Serial(write_timeout=None)
ser.baudrate = 9600
ser.port = 'COM4'
ser.open()

def cambio_color():
	ser.write(str.encode("a"))
	cadena = ser.readline().decode("utf-8").strip().split(",")
	ventana.configure(bg=a_rgb((int(cadena[0]), int(cadena[1]), int(cadena[2]))))

boton = ttk.Button(text="Detectar color", command=cambio_color)
boton.place(x=390, y=210, width=500, height=300)

ventana.title("Proyecto")
ventana.geometry("1280x720")
ventana.mainloop()
