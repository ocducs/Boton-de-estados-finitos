float tActual=0;
float t0=0;
float tf=0;
bool btnAnterior=LOW;
bool btnActual;
String msg="SIN FLANCO";
enum State{OFF, ON1, ON2};
State estado=OFF;
void setup() {
  // put your setup code here, to run once:
  pinMode(8,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
   
  if(Flanco()){
    //Serial.print(msg);
    Serial.print(" t:"+String(tf-t0));
   
    switch(estado){
    case OFF:
      estado=(tf-t0>1000)?ON1:OFF;break;
    case ON1:
      estado=(tf-t0>1000)?ON2:ON1;break;
    case ON2:
      estado=(tf-t0>1000)?ON1:ON1;break;
  }
    Serial.println(" estado actual: ");
    Serial.println(estado);
  }
}

bool Flanco(){
  tActual=millis();
  btnActual=digitalRead(8);   
  if(btnAnterior==HIGH && btnActual==LOW){
    t0=tActual; //tiempo inicial
    btnAnterior=btnActual;
  }
  if(btnAnterior==LOW && btnActual==HIGH){
    tf=tActual; //tiempo final
    btnAnterior=btnActual;
    return true;
  }
  btnAnterior=btnActual;
  return false;
}
    
  
