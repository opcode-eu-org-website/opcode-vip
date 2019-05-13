
# interfejs pseudo graficzny z użyciem Gtk 3

import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

window = Gtk.Window(title="Hello World")

def showDialog(caller):
	dialog = Gtk.MessageDialog(window, 0,
		Gtk.MessageType.QUESTION, Gtk.ButtonsType.YES_NO,
		"Ważne pytanie !!!")
	dialog.format_secondary_text("Tak czy nie?")
	
	response = dialog.run()
	if response == Gtk.ResponseType.YES:
		print("TAK !!!")
	elif response == Gtk.ResponseType.NO:
		print("NIE !!!")
	else:
		print("bez odpowiedzi!?")
	
	dialog.destroy()

button1 = Gtk.Button("Nacisnij mnie")
button1.connect("clicked", showDialog)

window.add(button1)

window.show_all()
window.connect("delete-event", Gtk.main_quit)
Gtk.main()
