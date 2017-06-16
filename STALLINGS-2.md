# Tipos de planifi#cación de procesos:

* A largo plazo: al crear un nuevo proceso le asigna un estado y es el encargado de finalizar procesos.
* A medio plazo: se encarga del swaping de procesos entre memoria principal y secundaria. 
* A corto plazo: qué proceso ejecutar en este momento. 


## A largo plazo 

Dado que determina qué procesos pasan a ejecutarse, controla el grado de multiprogramación del sistema. Para ellos, el planificador debe decidir cuando el SO está preparado para aceptar un proceso adicional y cual de los "jobs" en espera será aceptado y convertido en un nuevo proceso.

¿Cuándo aceptar un nuevo proceso? -> depende del grado de multiprogramación que queramos; a mayor grado, menor será el porcentaje de tiempo de CPU de los procesos en ejecución; por lo que este debe ser adecuado para satisfacer al mayor número posible de trabajos/procesos sin degradar el rendimiento de aquellos procesos en ejecución. 

Cuando un trabajo termina el planificador a largo plazo debe elegir si añadir uno o más trabajos a los procesos en ejecución; Además, si se excede un tiempo dado en que el procesador está ocioso, el planificador a largo plazo será llamado para crear nuevos procesos (podría ocurrir que todos los procesos estén bloqueados, ninguno termine y por eso no se puedan crear nuevos procesos). 

En sistemas multiusuario, un nuevo usuario que quiera iniciar un trabajo no tiene por qué esperar a que se llame al planificador de procesos por la finalización de otro, sino que, al solicitar la ejecución de un nuevo trabajo, llama al planificador a largo plazo y, si el sistema no está demasiado saturado, este ejecutará el trabajo. Si se direra el caso de que el sistema está soportando demasiados trabajos el usuario recibiría un mensaje informando de ello y el trabajo se colocaría en espera.

## A medio plazo

El número de procesos en ejecución (y por tanto, de programas cargados en memoria, PCBs etc... que ocupan memoria principal) es finito puesto que depende de la memoría principal de que dispongamos. Sin embargo, el SO puede aumentar el número de procesos en ejecución haciendo uso de la memoria virtual; es decir, mover la información de cada proceso en ejecución entre la memoria principal y memoria secundaria de forma que lo que un proceso necesita en memoria principal sólo esté ahí cuando el proceso tiene la CPU a su disposición, y no mientras el proceso no dispone de CPU. 
Para que ese uso de memoria virtual sea posible se requiere del planificador a medio plazo, que es el encargado de decidir cuando mover información relativa a un proceso de memoria principal a secundaria (en realidad, aunque un proceso no se este ejecutando en un momento dado, no hay por qué pasar su información a memoria secundaria si no hay necesidad de más memoria principal por parte de los otros procesos).

## A corto plazo

El planificador a corto plazo (también llamado dispatcher) es el planificador que más frecuéntemente se ejecuta, y su tarea es decidir qué proceso recibe CPU en cada momento. Los eventos que pueden llamar a este planificador son: interrupción de reloj (un proceso lleva mucho tiempo ejecutándose), Interrupción de E/S, Llamada al sistema, Señales (semáforos, monitores...) 

¿Cómo decide a qué proceso dar la CPU/una CPU? 

# Algoritmos de planificación.

## FIFO 

(también llamada FCFS == First Come, First served)

* Funciona mejor para procesos largos que para procesos cortos. 
* Los procesos se ejecutan en orden de llegada (hasta terminar o bloquearse) 

* INCONVENIENTE. Si tenemos procesos que emplean mucha CPU (mucho tiempo) y otros que constantemente tienen E/S, cuando los segundos se bloqueen y den paso a los primeros, estos utilizarán la CPU mucho tiempo, posiblemente más de lo que dura la interrupción de los de E/S. Esto probocará que los procesos con muchas E/S estén bloqueados más tiempo del que deberían y supondría un desperdicio de CPU. Si además los procesos que emplean mucha CPU se bloquearan todos y dieran la ejecución a los de E/S, estos sebloquearían rápidamente por una i.E/S y el procesador quedaría ocioso pues no habría ningún otro proceso para ejecutar. 

* INCONVENIENTE: Si un proceso muy corto llega justo después de uno muy largo, el corto estará en memoria principal todo el tiempo que dure el largo (mucho más de lo que dura él), por lo que se está manteniendo un trabajo en la lista de procesos de forma demasiado prolongada (ineficiente). 

* SOLUCIÓN: FIFO con prioridad.

## Round Robin 

Es una variación del criterio FIFO que añade inerrupciones regulares de reloj
