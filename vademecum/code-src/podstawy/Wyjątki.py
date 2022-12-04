
# Prawie wszystkie błędy w Pythonie mają postać wyjątków,
# które mogą zostać obsłużone blokiem try/except.

try:
  a = 5 / 0
except ZeroDivisionError:
  print("dzielenie przez zero")
except:
  print("inny błąd")

# Przy obsłudze błędów może przydać się instrukcja pusta "pass",
# która w tym przypadku pozwala na zignorowanie obsługi danego błędu.

try:
  slownik["a"] += 1
except:
  pass

# Powyższy kod zwiększy wartość związaną z kluczem "a" w słowniku "slownik",
# jednak gdy napotka błąd (np. słownik nie zawiera klucza "a") zignoruje go.

# Możemy także generować wyjątki z naszego kodu, służy do tego instrukcja raise,
# której należy przekazać obiektem dziedziczącym po \python{BaseException} np:

\begin{CodeFrame*}[python]{}
raise BaseException("jakiś błąd")
