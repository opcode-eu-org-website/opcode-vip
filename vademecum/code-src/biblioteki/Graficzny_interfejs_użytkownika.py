
# interfejs pseudo graficzny z użyciem biblioteki curces ...
# a tak naprawdę programu dialog z niej korzystającego

from dialog import Dialog
from time import sleep

d = Dialog(dialog="dialog")
# tak naprawdę jest to wraper
# wykorzystujący program o nazwie "dialog"
#
# jest w stanie (w ograniczonym zakresie)
# współpracować z innymi tego typu narzędziami
# (także działającymi w trybie graficznym)
#  takimi jak: whiptail, kdialog, ...
# d = Dialog(dialog="kdialog", compat="kdialog")

d.set_background_title("ABC ...")

res = d.yesno("Tak czy NIE?")

if res == d.OK:
	d.msgbox("TAK !!!")
else:
	d.msgbox("NIE !!!")

d.gauge_start("proszę czekać ... będzie rozmowa ...")
for i in range(0, 101, 5):
	d.gauge_update(i)
	sleep(1)
