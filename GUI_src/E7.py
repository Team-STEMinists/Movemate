from Bluetooth import *
from threading import Thread
from GUI import*


if __name__ == "__main__":
    global variable
    root = tk.Tk()
    widget = NewprojectWidget(root)
    widget.pack(expand=True, fill="both")
    T = Thread(target=BT, args=['COM11',9600])
    T.start()
    #T = Thread(target=BT, args=['COM7',9600])
    root.mainloop()
    #T.start()
