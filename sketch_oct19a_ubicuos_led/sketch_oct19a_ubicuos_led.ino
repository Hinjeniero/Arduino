#define dot 50
#define dash 250
#define wait 150
#define waitbetweenmsgs 2000
char humanPhrase[]="needhelpmessagefromthetitanicthisisnotaphisingmorsecodeneedhelp";
char humanLanguage[37] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q'
,'r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0'};
String morseLanguage[]={".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-",
"...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....",
"-....", "--...", "---..", "----.", "-----"};
  
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(sizeof(test));
  morseToLed(humanToMorse());
  delay(waitbetweenmsgs);
}

void morseToLed(String morsePhrase){
  int i;
  for (i=0; i<sizeof(morsePhrase); i++){
    if (morsePhrase[i] == '.'){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(dot);
      digitalWrite(LED_BUILTIN, LOW);
      delay(wait);
    }
    if (morsePhrase[i] == '-'){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(dash);
      digitalWrite(LED_BUILTIN, LOW);
      delay(wait);
    }
  }
}

String humanToMorse(){
  String morsePhrase = "";
  int i;
  for (i=0; i<sizeof(humanPhrase)-1; i++){
    int j;
    for(j=0; j<sizeof(humanLanguage)-1; j++){
       if (humanPhrase[i] == humanLanguage[j]){
        morsePhrase = String(morsePhrase + morseLanguage[j]);
        break;
      }
    }
  }
  Serial.println(humanPhrase);
  Serial.println(morsePhrase);
  return morsePhrase;
}

