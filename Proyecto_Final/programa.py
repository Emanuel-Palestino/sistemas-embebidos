import tkinter as tk
import serial

def a_rgb(rgb):
    return "#%02x%02x%02x" % rgb  

ventana = tk.Tk()
ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM4'
ser.open()

def cambio_color():
	cadena = ser.readline().decode("utf-8").strip().split(",")
	ventana.configure(bg=a_rgb((int(cadena[0]), int(cadena[1]), int(cadena[2]))))
	ventana.after(500, cambio_color)

ventana.after(0, cambio_color)
ventana.title("Proyecto")
ventana.geometry("1280x720")
ventana.mainloop()
