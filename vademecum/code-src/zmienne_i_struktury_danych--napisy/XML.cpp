
// wymaga pobrania biblioteki nagłówkowej rapidxml (http://rapidxml.sourceforge.net/)

#include "rapidxml.hpp"
namespace rapidxml { namespace internal {
	// fix bug in rapidxml https://sourceforge.net/p/rapidxml/bugs/16/
	template<class V, class C> V print_children(V, const xml_node<C>*, int, int);
	template<class V, class C> V print_element_node(V, const xml_node<C>*, int, int);
	template<class V, class C> V print_data_node(V, const xml_node<C>*, int, int);
	template<class V, class C> V print_cdata_node(V, const xml_node<C>*, int, int);
	template<class V, class C> V print_declaration_node(V, const xml_node<C>*, int, int);
	template<class V, class C> V print_comment_node(V, const xml_node<C>*, int, int);
	template<class V, class C> V print_doctype_node(V, const xml_node<C>*, int, int);
	template<class V, class C> V print_pi_node(V, const xml_node<C>*, int, int);
}}
#include "rapidxml_print.hpp"


#include <iostream>
#include <string.h>

int main() {
	char xmlString[1024];
	strncpy(xmlString,
		"<a>"
			"<b>A<h>qwe ... rty</h></b>"
			"ABCD...HIJ..."
			"<c x=\"q\" w=\"p p\">EE F</c>"
			"<g y=\"zz\" />"
			"<c x=\"pp\">123 <d rr=\"oo\">456</d> 78 90.</c>"
		"</a>",
		1024
	);
	
	// utworzenie obiektu drzewa XMLowego w oparciu o napis
	rapidxml::xml_document<> xmlDoc;
	xmlDoc.parse<0>(xmlString);
	
	// pobranie głównego węzła
	rapidxml::xml_node<>* xmlRoot = xmlDoc.first_node();
	
	std::cout << "nazwa głównego elementu to: " << xmlRoot->name() << "\n";
	std::cout << "jego zawartość tekstowa to: " << xmlRoot->value() << "\n";
	std::cout << "jego wartość to: {{{{" << *xmlRoot << "}}}}\n";
	
	std::cout << "jego potomkowie to: \n";
	rapidxml::xml_node<>* xmlNode = xmlRoot->first_node();
	while(xmlNode) {
		std::cout << " " << xmlNode->name() << " : ";
		rapidxml::print( std::cout, *xmlNode, rapidxml::print_no_indenting );
		// rapidxml::print() może zapisywać także do napisu
		std::cout << "\n";
		xmlNode = xmlNode->next_sibling();
	}
	
	std::cout << "pierwszy węzeł c ma atrybuty:\n";
	xmlNode = xmlRoot->first_node("c");
	if(xmlNode) {
		rapidxml::xml_attribute<>* xmlAtrib = xmlNode->first_attribute();
		while(xmlAtrib) {
			std::cout << xmlAtrib->name() << " = " << xmlAtrib->value() << "\n";
			xmlAtrib = xmlAtrib->next_attribute();
		}
	}
	
	// modyfikacje dokumentu:
	
	// zmiana nazwy i zawartości elementu
	xmlNode = xmlRoot->first_node("g");
	if (xmlNode) {
		xmlNode->name("noweGG");
		xmlNode->value("!@#$");
	}
	
	// zmiana nazwy i wartości atrybutu
	xmlNode = xmlRoot->first_node("c");
	if(xmlNode) {
		rapidxml::xml_attribute<>* xmlAtrib = xmlNode->first_attribute();
		while(xmlAtrib) {
			if (xmlAtrib->name() == std::string("w")) {
				xmlAtrib->name("uu");
				xmlAtrib->value("1 2 3");
				break;
			}
			xmlAtrib = xmlAtrib->next_attribute();
		}
	}
	
	// usuwanie wszystkich potomków ostatniego <c>
	xmlNode = xmlRoot->last_node("c");
	xmlNode->remove_all_nodes();
	xmlNode->value("");
	// usuwanie wszystkich atrybutów ...
	xmlNode->remove_all_attributes();
	// są też funkcje usuwające wskazanego potomka lub atrybut:
	// remove_node() i remove_attribute()
	
	// dodawanie atrybutów
	xmlNode->append_attribute(
		xmlDoc.allocate_attribute("abc", "098")
	);
	xmlNode->append_attribute(
		xmlDoc.allocate_attribute("qwe", "...")
	);
	// powyższa metoda dodaje na koniec, można także dodawać na początek:
	// prepend_attribute() lub na wskazaną pozycję insert_attribute()
	
	// dodawanie potomków
	rapidxml::xml_node<>* xmlNode2;
	xmlNode2 = xmlDoc.allocate_node(rapidxml::node_data, NULL);
	xmlNode2->value("ert");
	xmlNode->append_node(xmlNode2);
	
	xmlNode2 = xmlDoc.allocate_node(rapidxml::node_element, "kk");
	xmlNode2->value("uio");
	xmlNode->append_node(xmlNode2);
	
	xmlNode2 = xmlDoc.allocate_node(rapidxml::node_data, NULL);
	xmlNode2->value("bnm");
	xmlNode->append_node(xmlNode2);
	
	// podobnie jak atrybuty nody też możemy dodawać na początku
	// prepend_node() lub na dowolnej pozycji insert_node()
	
	// wypisanie zmienionego dokumentu
	std::cout << xmlDoc;
}
