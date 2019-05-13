class PID {
	// poprzednia różnica między wartością zadaną a otrzymaną
	// (poprzedni błąd regulacji / uchyb)
	float lastDiff;
	
	// poprzednia wartość otrzymana (zmienna procesu)
	float lastVal;
	
	// część całkująca, akumulowana pomiędzy krokami
	float integral;
	
public:
	// nastawa - wartość zadana
	float setPoint;
	
	// wartość wyjścia dla sterowania krokowego
	// (akumulacja w układzie realizującym)
	float outStep;
	
	// wartość wyjścia dla sterowania sygnałem
	float outValue;
	
	// parametry regulatora PID
	float Kp, Ki, Kd;
	
	// limity wartości sterowanej
	float outValueMin, outValueMax;
	
	// konstruktor - inicjalizacja parametrów
	PID (
		float initVal, float sp,
		float kp, float ki, float kd, float min, float max
	) :
		lastDiff(0), lastVal(initVal), integral(0),
		setPoint(sp), outStep(0), outValue(0),
		Kp(kp), Ki(ki), Kd(kd),
		outValueMin(min), outValueMax(max)
	{}
	
	int doStep(float inputVal, float stepTime) {
		// obliczmy aktualny błąd regulacji
		// (na podstawie odczytanej wartości wejściowej)
		float diff = setPoint - inputVal;
		
		// wyłączamy regulację gdy prowadziłby do przesterowania
		if (outValue > outValueMax && diff > 0)
			return 1;
		if (outValue < outValueMin && diff < 0)
			return -1;
		
		// całkowanie przybliżamy jako jako suma pól trapezów
		integral += (diff + lastDiff) / 2 * stepTime;
		
		// różniczkowanie przybliżamy jako tangens nachylenia
		// prostej pomiędzy poprzednim krokiem a obecnym
		// celem złagodzenia odpowiedzi na zmiany wartości zadanej
		// różniczkujemy sygnał wejściowy
		float derivative = -(inputVal - lastVal) / stepTime;
		// a nie błąd regulacji: derivative = (diff - lastDiff) / stepTime;
		
		// obliczenie wartości sygnału sterującego na podstawie tego kroku
		outStep   = Kp*diff + Ki*integral + Kd*derivative;
		
		// akumulacja sygnału sterującego
		outValue += outStep;
		
		// zapamiętanie aktualnego błędu regulacji
		// jako poprzedni dla następnego kroku
		lastDiff = diff;
		
		// zapamiętanie aktualnej wartości wejściowej
		// jako poprzedniej dla następnego kroku
		lastVal  = inputVal;
		
		return 0;
	}
};

int main() {
	PID pid(readInput(), 21.0, 1.0, 0.0, 0.0, -100.0, 100.0);
	
	// okres działania algorytmu [us]
	unsigned int stepTime = 250000;
	
	// pętla algorytmu
	while(1) {
		// odczyt wejścia
		float curVal = readInput();
		
		// obliczenie wartości sterującej z użyciem PID
		pid.doStep( curVal, stepTime );
		
		// wystawienie wartości sterującej
		setOutput(pid.outValue);
		
		// odczekanie do następnego kroku
		usleep(stepTime);
	}
}
