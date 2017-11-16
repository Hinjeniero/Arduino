const char humanAlphabet[37] ={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0','\0'};
const char* const morseAlphabet[]={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",
".--","-..-","-.--","--..",".----","..---","...--","....-",".....","-....","--...","---..","----.","-----"};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  char rabo[80];
  char* test = charToMorse('0');
  strcpy(rabo, test);
  char* test2 = charToMorse('\n');
  strcat(rabo, test2);
  char* test3 = charToMorse('9');
  strcat(rabo, test3);
  Serial.print(rabo);
}

void concatenateArrays(char* arrayA, char* arrayB){
  
}
void loop() {
  // put your main code here, to run repeatedly:

}

char* charToMorse(char humanChar){
  int i;
  for(i=0; humanAlphabet[i] != '\0'; i++){
    Serial.println(i);
    Serial.println(humanAlphabet[i]);
    if (humanChar == humanAlphabet[i])//If the human char has a traslation in morse
      return morseAlphabet[i];} //We return the cell (index of the traduction)
  return 0;//IF it doesn't exist, return a null buffer
}

