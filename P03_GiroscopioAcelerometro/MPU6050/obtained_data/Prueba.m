clear all
clc
%warning off

%pkg load instrument-control
receiveFlag = false;
newData = false;
ts = 0.1;
t = 0:0.1:10;
maxValue = 1023;
minValue = 0;

value1 = zeros(1, length(t));
value2 = zeros(1, length(t));
valueN1 = zeros(1, length(t));
valueN2 = zeros(1, length(t));

arduino = serialport("COM4", 9600);

pause(4);

% Variables para almacenar los valores
primeros_valores = zeros(1, 3);
segundos_valores = zeros(1, 3);

for k = 1:length(t)
    tic;
    flush(arduino,"output"); %srl_flush(arduino);
    data = read(arduino, 11, "char");

    % Espera hasta que se reciba un paquete completo
    C = char(data);

    contador_primeros = 0;
    contador_segundos = 0;
    
    for i = 1:length(C)
        if (C(i) >= '0') && (C(i) <= '9')
            if contador_primeros < 3
                contador_primeros = contador_primeros + 1;
                primeros_valores(contador_primeros) = str2double(C(i));
            elseif contador_primeros == 3 && contador_segundos < 3
                contador_segundos = contador_segundos + 1;
                segundos_valores(contador_segundos) = str2double(C(i));
            end
        end
    end
  
    while toc < ts
    end
    tiempo(k) = toc;

end

disp('Primeros tres valores:');
disp(primeros_valores);
disp('Segundos tres valores:');
disp(segundos_valores);

% Agregar un cero al principio de los valores
primeros_valores = [0, primeros_valores];
segundos_valores = [0, segundos_valores];

disp('Primeros cuatro valores:');
disp(primeros_valores);
disp('Segundos cuatro valores:');
disp(segundos_valores);
