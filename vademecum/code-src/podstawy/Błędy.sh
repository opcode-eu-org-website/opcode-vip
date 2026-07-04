
# Błędy w świecie shellowym sygnalizowane są przez niezerowy kod powrotu
# może on być sprawdzany przy pomocy komendy if, używany w łączeniu poleceń itd.

# Możliwe jest też nakazanie przerwania skryptu po wystąpieniu pierwszej
# komendy która zwróciła niezerowy kod powrotu, który nie był obsłużony np. z użyciem if'a

set -e


# Działający program może zostać zakończony w sposób niespodziewany,
# np. na skutek działania sygnałów.
# Dotyczy to również basha wykonującego jakiś skrypt powłoki.

# Możemy nawet samodzielnie zażądać przerwania wykonywania skryptu przy pierwszym błędzie
# (pierwszym poleceniu które zwróci nieobsłużony niezerowy kod powrotu) wydając polecenie `set -e`.

# Niekiedy chcemy móc w takiej sytuacji wykonać jakieś działania.
# Możliwe jest to z użyciem instrukcji `trap`, która pozwala na zdefiniowanie procedury
# obsługi sygnałów (oczywiście tych które mamy prawo obsłużyć) i innych zdarzeń. Na przykład:

trap '{ echo "to koniec"; }' EXIT

# Spowoduje wypisanie "to koniec" w momencie kończenia pracy powłoki.
# Umieszczenie takiej instrukcji w kodzie skryptu spowoduje wypisanie tego komunikatu
# niezależnie od przyczyny zakończenia (dojście do końca skryptu wywołanie polecenia exit,
# przerwanie Control C, czy też otrzymanie innego przechwytywalnego sygnału).

false

echo "to się nie wykona ze względu na set -e i false"
