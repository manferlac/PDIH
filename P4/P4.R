#install.packages('tuneR', dep=TRUE)
#install.packages('seewave', dep=TRUE)
#install.packages('soundgen', dep=TRUE)

library(tuneR)
library(seewave)
library(audio)

# establecemos el directorio de trabajo
setwd("/Users/manferlac/Desktop/PDIH/P4/sonidos")
# establecemos el reproductor para los sonidos
setWavPlayer('/usr/bin/afplay')

# Ejercicio 1 - Leemos los ficheros de sonido
oveja <- readWave('oveja.wav')
oveja
perro  <- readWave('perro.wav')
perro


# Ejercicio 2 - Dibujamos la forma de onda de ambos sonidos
plot( extractWave(oveja, from = 1, to = 19764) )
plot( extractWave(perro, from = 1, to = 159732) )

# Ejercicio 3 - Mostramos la información de las cabeceras de ambos sonidos
str(oveja)
str(perro)

# Ejercicio 4 - Unimos ambos sonidos en uno nuevo
sonidoNuevo <- pastew(oveja, perro,at="end", output = "Wave")
# mostramos la info del sonido nuevo
sonidoNuevo

# Ejercicio 5 - dibujamos la onda de la señal nueva
plot( extractWave(sonidoNuevo, from = 1, to = length(sonidoNuevo)) )

# Ejercicio 6 - Pasamos el filtro de frecuencia
f <- sonidoNuevo@samp.rate    #44100
filtro <- bwfilter(sonidoNuevo, f = f, channel = 1, n = 1, from = 1000, to = 4000, bandpass = TRUE, listen = FALSE, output = "Wave")

# Ejercicio 7 - Almacenar la señal en un fichero wav
writeWave(filtro, file.path("mezcla.wav"))

# Ejercicio 8 - Cargar un nuevo archivo de sonido, aplicarle eco y a continuación darle la vuelta al sonido. Almacenar la señal obtenida como un fichero WAV denominado “alreves.wav”
gato <- readMP3('gato.mp3')
gato_con_eco <- echo(gato,f=22050,amp=c(0.8,0.4,0.2),delay=c(1,2,3),output = "Wave")
gato_con_eco@left <- 10000 * gato_con_eco@left
gato_alreves <- revw(gato_con_eco,output = "Wave")
writeWave(gato_alreves,file.path("alreves.wav"))
