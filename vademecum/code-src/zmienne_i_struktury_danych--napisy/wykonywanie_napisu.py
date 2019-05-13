
# dla kodu pythonowego
a="""print("ppp")
b=13-17
"""
exec(a)
print(b)

# dla wyrażeń
a="9+7"
b = eval(a)
print(b)

# lub
exec("c="+a)
print(c)

# oczywiście napis może pochodzić z
# dowolnego źródła, może być też
# treścią całego skryptu pythonowego:
#  exec(open("plik.py").read())
