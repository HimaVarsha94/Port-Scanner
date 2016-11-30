#!/usr/bin/python
# -*- coding: utf-8 -*-

from Tkinter import * #Tk,Frame, Text, BOTH, W, N, E, S
from ttk import Frame, Button, Label, Style
import Tkinter as tk 

root = Tk()

class Example(Frame):

    def __init__(self, parent):
        Frame.__init__(self, parent)   
         
        self.parent = parent
        
        self.initUI()
        
    def initUI(self):
      
        self.parent.title("PORT SCANNER")
        self.style = Style()
        self.style.theme_use("default")
        self.pack(fill=BOTH, expand=1)

	self.style.configure("TFrame", background="#2E2E2E")

        self.columnconfigure(1, weight=1)
        self.columnconfigure(3, pad=7)
        self.rowconfigure(3,weight=1)
        self.rowconfigure(5, pad=7)
		
        def syn():
		import os
		addr = E1.get()
		os.system("./tcp-syn " + addr + " >test1.txt")
		with open("test1.txt") as f:
    			content = f.readlines()
		for i in range(len(content)):	
			area1.insert(INSERT,content[i])
			area1.insert(INSERT,"\n")    
	
        def tcp():
		import os
		addr = E1.get()
		os.system("./tcp " + addr +" >test1.txt")
		with open("test1.txt") as f:
    			content = f.readlines()
		for i in range(len(content)):	
			area1.insert(INSERT,content[i])
			area1.insert(INSERT,"\n")
        def udp():
		import os
		str1 = E1.get()
		os.system("./udp "+ str1 +" >test1.txt")
		with open("test1.txt") as f:
    			content = f.readlines()
		for i in range(len(content)):	
			area1.insert(INSERT,content[i])
			area1.insert(INSERT,"\n")
        def ping():
		import os
		str1 = E1.get()
		os.system("./ping "+ str1 +" >test1.txt")
		with open("test1.txt") as f:
    			content = f.readlines()
		for i in range(len(content)):	
			area1.insert(INSERT,content[i])
			area1.insert(INSERT,"\n")

	def clear_text():
		area1.delete(1.0,END)
	
	label1 = Label( root, text="IP ADDRESS")
	root.configure(background="#8A0829")
	E1 = Entry(root, bd =10)
	label1.pack()
	E1.pack(pady=30,padx=1,ipadx=5)	
	
	area1 = Text(self)
        area1.grid(row=1, column=0, columnspan=1, rowspan=2, padx=2,pady=3, sticky=W+N)
	area1.configure(background='#F5A9BC') 	   
	
        syn_btn = Button(self, text="TCP/SYN SCAN",command=syn)
        syn_btn.grid(row=1, column=3,sticky = N)

        tcp_btn = Button(self, text="TCP SCAN",command=tcp)
        tcp_btn.grid(row=2, column=3, pady=5)

        udp = Button(self, text="UDP SCAN",command = udp)
        udp.grid(row=3, column=3, pady=5)

        ping= Button(self, text="PING",command=ping)
        ping.grid(row=4, column=3,pady=10)

        tr = Button(self, text="TRACEROUTE")
        tr.grid(row=5, column=3,pady=10) 

	tr = Button(self, text="CLEAR SCREEN",command=clear_text)
        tr.grid(row=6, column=3,pady=10,sticky=S)            
             

def main():

    root.geometry("350x300+300+300")
    app = Example(root)
    root.mainloop()  


if __name__ == '__main__':
    main()  
