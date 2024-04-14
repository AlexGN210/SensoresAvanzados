function [TrainInput,TrainOutput,TestInput,TestOutput]  = divideData (DataInput,DataOutput,percentage)
  Q=size(DataInput,2);
  
  sizeTrain=round(percentage*Q);
  sampleTrain = randsample(Q,sizeTrain);
  index=1;
  sampleTest=zeros(1,Q-sizeTrain);
  for j=1:Q
      flag=0;
  for i=1:sizeTrain
    if j==sampleTrain(i)
      flag=1;
      break;
    end
  end
  if flag==0
     sampleTest(index)=j;
     index=index+1;
  end
  end

  TrainInput=DataInput(:,sampleTrain);
  TestInput=DataInput(:,sampleTest);
  
  TrainOutput=DataOutput(:,sampleTrain);
  TestOutput=DataOutput(:,sampleTest);
end