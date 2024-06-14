// Código Arduino para suavizar a transição entre as cores do arco-íris em um LED RGB

// Define os pinos do LED RGB
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

// Define a velocidade de transição entre as cores
const int transitionSpeed = 35; // Tempo de transição em milissegundos

// Variável para controlar a posição atual no espectro de cores
int rainbowOffset = 0;

void setup() {
  // Inicializa os pinos como saídas
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Atualiza a cor do LED RGB com base na posição atual no espectro de cores
  rainbow(rainbowOffset); // Chama a função para transição de cor com a posição atual no espectro de cores
  rainbowOffset++; // Incrementa a posição atual no espectro de cores
  if (rainbowOffset >= 360) {
    rainbowOffset = 0; // Reinicia a posição no espectro de cores quando atinge 360
  }
}

// Função para fazer a transição de cor suave
void rainbow(int offset) {
  // Define a cor com base no offset
  int red = calculateColor(offset);
  int green = calculateColor(offset + 120);
  int blue = calculateColor(offset + 240);

  // Atualiza a cor do LED RGB suavemente
  fadeToColor(redPin, red);
  fadeToColor(greenPin, green);
  fadeToColor(bluePin, blue);
}

// Função auxiliar para calcular o valor de cor
int calculateColor(int value) {
  // Garante que o valor esteja no intervalo [0, 359]
  value = value % 360;
  // Mapeia o valor de [0, 359] para [0, 255]
  return map(value, 0, 359, 0, 255);
}

// Função auxiliar para suavizar a transição entre as cores
void fadeToColor(int pin, int targetColor) {
  int currentColor = analogRead(pin);
  if (currentColor < targetColor) {
    for (int i = currentColor; i <= targetColor; i++) {
      analogWrite(pin, i);
      delay(transitionSpeed);
    }
  } else if (currentColor > targetColor) {
    for (int i = currentColor; i >= targetColor; i--) {
      analogWrite(pin, i);
      delay(transitionSpeed);
    }
  }
}
