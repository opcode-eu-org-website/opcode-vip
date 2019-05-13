
import xml.etree.ElementTree as xml
# Python oferuje także inne niz ElementTree moduły do obsługi XML
# także wspierające DOM

d = """<a>
	<b>A<h>qwe ... rty</h></b>
	ABCD... &amp;&apos; HIJ...
	<c x="q" w="p p">EE FĄ</c>
	<g y="zz" />
	<c x="pp">123 <d rr="oo">456</d> 78 90.</c>
</a>"""

rootNode = xml.fromstring(d)

# pobieranie informacji z dokumentu

print("nazwa głównego elementu to:", rootNode.tag)
print("jego zawartość tekstowa to:", rootNode.text)
print("jego pełna zawartość tekstowa to:", "".join(rootNode.itertext()))
print("jego wartość to: {{{{", xml.tostring(rootNode, encoding="unicode") ,"}}}}")

print("jego potomkowie to:")
for c in rootNode:
	print(" ", c.tag, ":", xml.tostring(c, encoding="unicode"))

print("pierwszy węzeł c ma atrybuty:")
try:
	ci = rootNode.iter("c")
	print(next(ci).attrib)
except StopIteration:
	print(" [brak takiego węzła]")

# modyfikacje dokumentu

# zmiana nazwy i zawartości elementu
try:
	ci = rootNode.iter("g")
	cc = next(ci);
	cc.tag = "noweGG"
	cc.text = "!@#$"
except StopIteration: pass

# zmiana nazwy i wartości atrybutu
try:
	ci = rootNode.iter("c")
	cc = next(ci);
	del cc.attrib["w"]
	cc.attrib["uu"] = "1 2 3"
except StopIteration: pass

try:
	cc = next(ci);
	# usuwanie wszystkich potomków drugiego <c>
	cc.clear()
	# jest też remove() które usuwa wskazany element
	
	# usuwanie wszystkich atrybutów ...
	cc.attrib.clear()
	
	se = xml.SubElement(cc, "kk", attrib={"aa":str(45)})
	se.text = "uio"
	se = xml.SubElement(cc, None)
	se.text = "bnm"
	
	# możliwe jest też wstawienie w podanym miejscu
	se = xml.Element(None)
	se.text = "ert"
	cc.insert(0, se)
except StopIteration: pass

print(xml.tostring(rootNode, encoding="unicode"))
