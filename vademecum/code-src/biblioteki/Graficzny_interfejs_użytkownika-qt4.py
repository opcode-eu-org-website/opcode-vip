
# interfejs pseudo graficzny z użyciem Qt4

import sys
from PyQt4 import QtGui, QtCore

app = QtGui.QApplication(sys.argv)

win = QtGui.QWidget()
win.resize(250, 150)
win.move(300, 300)
win.setWindowTitle('ABC ...')

def showDialog():
	reply = QtGui.QMessageBox.question(None, 'Message',
		"Tak czy nie?", QtGui.QMessageBox.Yes | 
		QtGui.QMessageBox.No, QtGui.QMessageBox.No)
	
	if reply == QtGui.QMessageBox.Yes:
		print("YES")
	elif reply == QtGui.QMessageBox.No:
		print("NO")
	else:
		print("cos innego?!")

button = QtGui.QPushButton('Nacisnij mnie', win)
button.clicked.connect(showDialog)
button.resize(button.sizeHint())
button.move(
	250/2-button.sizeHint().width()/2,
	150/2-button.sizeHint().height()/2
)

win.show()
