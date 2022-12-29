import tkinter as tk
import tkinter.ttk as ttk

variable = {"W":None,"I":None,"T":None}

class NewprojectWidget(ttk.Frame):
    def __init__(self, master=None, **kw):
        super(NewprojectWidget, self).__init__(master, **kw)
        self.weght = tk.Message(self)
        self.W = tk.StringVar(value='Exercise')
        self.weght.configure(
            font="{5} 20 {}",
            justify="right",
            text='Exercise',
            textvariable=self.W,
            width=200)
        self.weght.pack(ipadx=50, ipady=50, padx=50, pady=50, side="right")
        self.Iteration = tk.Message(self)
        self.I = tk.StringVar(value='Repetition\n')
        self.Iteration.configure(
            font="{5} 20 {}",
            justify="right",
            text='Iteration',
            textvariable=self.I,
            width=200)
        self.Iteration.pack(ipadx=50, ipady=50, padx=50, pady=50, side="left")
        label2 = ttk.Label(self)
        self.img_ttt = tk.PhotoImage(file="ttt.png")
        label2.configure(image=self.img_ttt, text='label2')
        
        label2.pack(side="top")
        progressbar1 = ttk.Progressbar(self)
        self.P = tk.StringVar(value='80')
        progressbar1.configure(
            mode="determinate",
            orient="horizontal",
            value=80,
            variable=self.P)
        progressbar1.pack(ipadx=5, ipady=5, padx=5, pady=5, side="top")
        self.configure(height=500, relief="groove", width=400)
        self.pack(side="top")

        self.Name = tk.Message(self)
        self.ID = tk.StringVar(value='Name')
        self.Name.configure(
            font="{5} 20 {}",
            justify="right",
            text='Name',
            textvariable=self.ID,
            width=200)
        self.Name.pack(ipadx=50, ipady=50, padx=50, pady=50, side="bottom")

        self.Time = tk.Message(self)
        self.T = tk.StringVar(value='Time')
        self.Time.configure(
            font="{5} 20 {}",
            justify="right",
            text='Time',
            textvariable=self.T,
            width=200)
        self.Time.pack(ipadx=50, ipady=50, padx=50, pady=50, side="bottom")

        global variable
        variable["W"]= self.W
        variable["I"]= self.I
        variable["ID"] = self.ID
        variable["T"] = self.T
        variable["P"] = self.P





