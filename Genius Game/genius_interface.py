import tkinter as tk
import tkinter.font as tkFont
import time
import serial

ser = serial.Serial(port='COM3', baudrate=9600, timeout=1)


screen = tk.Tk()

fontStyle = tkFont.Font(family="Zing Script Rust SB Demo Base", size=40)
fontStyle2 = tkFont.Font(family="Zing Script Rust SB Demo Base", size=45)
screen.title("Genius Game")
screen.geometry("1209x680")
screen.resizable(width=False, height=False)
screen.configure(background="#112030")

image_background = tk.PhotoImage(file="screen_background.PNG")
image_background.subsample(1, 1)

label_image = tk.Label(image=image_background)
label_image.place(x=0, y=0, relwidth=1.0, relheight=1.0)

text = tk.StringVar()
pont = tk.StringVar()
game_status = tk.Label(screen, textvariable=text, bg="#112030", fg="white",
                       font=fontStyle).place(relx=.5, rely=.3, anchor="center")
pont_status = tk.Label(screen, textvariable=pont, bg="#112030", fg="white",
                       font=fontStyle2).place(relx=.5, rely=.4, anchor="center")

text.set("PRESS ANY BUTTON TO START")
pont.set("")
screen.update_idletasks()
screen.update()
time.sleep(5)
matchs = -1

while 1:
    msg = ser.readline().decode('utf-8', 'ignore').strip()
    print(msg)
    if msg == "-1":
        text.set("PRESS ANY BUTTON TO START")
        pont.set("")
    elif msg == "-2":
        text.set("STARTING IN...")
        pont.set("3")
        screen.update_idletasks()
        screen.update()
        time.sleep(1)
        pont.set("2")
        screen.update_idletasks()
        screen.update()
        time.sleep(1)
        pont.set("1")
        screen.update_idletasks()
        screen.update()
        time.sleep(1)
        text.set(f"SCORE")
        pont.set("")

    elif msg == "-3":
        text.set("GAME OVER!!")
        pont.set("")
        screen.update_idletasks()
        screen.update()
        matchs = -1

    else:
        if msg.isnumeric():
            matchs += 1
            pont.set(matchs)

    screen.update_idletasks()
    screen.update()
