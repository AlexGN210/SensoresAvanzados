clear all
clc

receiveFlag = false;
newData = false;

ts=0.1;
t=0:1:100;

maxValue=1023;
minValue=0;

value1=zeros(1,length(t));
value2=zeros(1,length(t));

arduino = serialport("COM5",9600);

pause(4);

disp('Recolectando Datos....')

for k=1:length(t)
    tic;
    flush(arduino); % Limpiar el buffer de entrada
    data = read(arduino,11,"char");
    C=char(data)
    receiveFlag = false;
    Aux = '';

    for i=1:length(C) %<0555,0941>
        if receiveFlag == true
            if C(i) ~= '>' 
                Aux=[Aux C(i)];
            else
                newData=true;
                break; % Salir del bucle una vez que se ha encontrado '>'
            end
        elseif C(i) == '<'
            receiveFlag = true;
        end
    end

    if newData == true
        Data=strsplit(Aux,',');
        value1(k)=(str2double(Data{1,1})/10);
        value2(k)=(str2double(Data{1,2})/10);
        newData=false;
    end

    % Esperar antes de la próxima lectura
    while toc < ts
    end

    tiempo(k) = toc;
end
disp('Datos Recolectados...')
arduino = [];

% ft de primer orden para el MPL311
sys1 = tfest(value1',0,2);

% ft de primer orden para el DHT11
sys2 = tfest(value2', 1, 0);

subplot(21)
plot(t,value1);
title('MPL311');
subplot(22)
plot(t,value2);
title('DHT11');