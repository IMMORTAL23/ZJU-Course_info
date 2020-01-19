clc;
clear;

P=xlsread('人员安排.xlsx','L2:M492');
A=xlsread('人员.xlsx','D2:I492');
[~,DC]=xlsread('人员.xlsx','B2:C492');
DD=zeros(491,2);  %将目的地文本转换成数字
DQ=zeros(491,6);  %将目的地转换为偏移量

for i=1:491
    for j=1:2
        if DC{i,j}(1)=='B'
            DD(i,j)=1;
        end
        if DC{i,j}(1)=='G'
            DD(i,j)=2;
        end
        if DC{i,j}(1)=='P'
            DD(i,j)=3;
        end
        if DC{i,j}(1)=='Q'
            DD(i,j)=4;
        end
        if DC{i,j}(1)=='S'
            DD(i,j)=5;
        end
        if DC{i,j}(1)=='Y'
            DD(i,j)=6;
        end
    end
end

for i=1:491
    for j=1:6
        if DD(i,1)==j
            DQ(i,j)=100;
        else
            if DD(i,2)==j
                DQ(i,j)=0;
            else 
                if DD(i,2)==0
                    DQ(i,j)=0;
                else
                    DQ(i,j)=1;
                end
            end
        end
    end
end

B=zeros(64,6);
for i=1:64
    bvalue=i;
    for j=1:6
        if bvalue>2^(6-j)
            B(i,j)=1;
            bvalue=bvalue-2^(6-j);
        end
    end
end

IP=cell(491,2);
for i=1:491
   ht=A(i,1)*2^5+A(i,2)*2^4+A(i,3)*2^3+A(i,4)*2^2+A(i,5)*2+A(i,6)+1;
   IP{i,1}=ht;
   IP{i,2}=zeros(1,6);
   for j=1:6
       IP{i,2}(j)=DQ(i,j);
   end
end

T1=cell(35,6);
for i=1:35
    for j=1:6
        T1{i,j}=cell(1,2);
        T1{i,j}{1,1}=0;
        T1{i,j}{1,2}=cell(1,7);
        for k=1:7
            T1{i,j}{1,2}{1,k}=cell(1,2);
        end
    end
end

index=zeros(35,6);
for i=1:491
    t1=P(i,2);
    t2=P(i,1);
    T1{t1,t2}{1,1}=T1{t1,t2}{1,1}+1;
    index(t1,t2)=index(t1,t2)+1;
    T1{t1,t2}{1,2}{1,index(t1,t2)}{1,1}=i;
    T1{t1,t2}{1,2}{1,index(t1,t2)}{1,2}=IP{i,2};
end

T2=T1;
for i=1:6
    for j=1:35
        if T2{j,i}{1,1}==0
            for k=j:35
                if T2{k,i}{1,1}~=0
                    T2{j,i}=T2{k,i};
                    T2{k,i}{1,1}=0;
                    break;
                end
            end
        end
    end
end

%手调
temp=T2{1,1};
T2{1,1}=T2{13,1};
T2{13,1}=temp;

temp=T2{6,2};
T2{6,2}=T2{7,2};
T2{7,2}=temp;

temp=T2{11,5};
T2{11,5}=T2{13,5};
T2{13,5}=temp;

temp=T2{8,6};
T2{8,6}=T2{13,6};
T2{13,6}=temp;

C=zeros(15,6);
for i=1:15
    for j=1:6
        if T2{i,j}{1,1}>0
            min=10000;
            for k=1:6
                minsum=0;
                for x=1:T2{i,j}{1,1}
                    minsum=minsum+T2{i,j}{1,2}{1,x}{1,2}(k);
                end
                if minsum<min
                    min=minsum;
                end
            end
            C(i,j)=min;
        end
    end
end

Psum=0;
for i=1:15
    for j=1:6
        Psum=Psum+C(i,j);
    end
end
disp(Psum);


T3=T2;
for cnt=1:2
for i1=1:15
    for j1=1:6
        if T3{i1,j1}{1,1}>0
            for x1=1:T3{i1,j1}{1,1}
                cnt1=0;
                for x11=1:T3{i1,j1}{1,1}
                    if DD(T3{i1,j1}{1,2}{1,x1}{1,1},1)~=DD(T3{i1,j1}{1,2}{1,x11}{1,1},1)
                        cnt1=cnt1+1;
                    end
                end
                
                for k=1:6
                    if T3{i1,j1}{1,2}{1,x1}{1,2}(k)==100
                        z1=k;
                    end
                end
                for i2=1:15
                    for j2=1:6
                        if ~(i2==i1&&j2==j1)&&T3{i2,j2}{1,1}>0
                            for x2=1:T3{i2,j2}{1,1}
                                cnt2=0;
                                for x12=1:T3{i2,j2}{1,1}
                                    if DD(T3{i2,j2}{1,2}{1,x2}{1,1},1)~=DD(T3{i2,j2}{1,2}{1,x12}{1,1},1)
                                    cnt2=cnt2+1;
                                    end
                                end
                                
                                z=0;
                                for k=1:6
                                    if T3{i2,j2}{1,2}{1,x2}{1,2}(k)==100
                                        z2=k;
                                    end
                                end
                                if z1==z2
                                    z=1;
                                end
                                
                                time=0;
                                if A(T3{i1,j1}{1,2}{1,x1}{1,1},j2)==1&&A(T3{i2,j2}{1,2}{1,x2}{1,1},j1)==1
                                    time=1;
                                end
                                
                                if z==1&&time==1
                                
                                if cnt1>2
                                    T3{i1,j1}{1,2}{1,x1}{1,2}(z1)=0;
                                end
                                if cnt2>2
                                    T3{i2,j2}{1,2}{1,x2}{1,2}(z2)=0;
                                end
                                
                                temp=T3{i2,j2}{1,2}{1,x2};
                                T3{i2,j2}{1,2}{1,x2}=T3{i1,j1}{1,2}{1,x1};
                                T3{i1,j1}{1,2}{1,x1}=temp;
                                
                                min1=10000;
                                for k=1:6
                                    if k~=z1
                                    minsum1=0;
                                    for x=1:T3{i1,j1}{1,1}
                                         minsum1=minsum1+T3{i1,j1}{1,2}{1,x}{1,2}(k);
                                    end
                                    if minsum1<min1
                                        min1=minsum1;
                                    end
                                    end
                                end
                                min2=10000;
                                for k=1:6
                                    if k~=z2
                                    minsum2=0;
                                    for x=1:T3{i2,j2}{1,1}
                                         minsum2=minsum2+T3{i2,j2}{1,2}{1,x}{1,2}(k);
                                    end
                                    if minsum2<min2
                                        min2=minsum2;
                                    end
                                    end
                                end
                                
                                if cnt2>2
                                    T3{i1,j1}{1,2}{1,x1}{1,2}(z2)=100;
                                end
                                if cnt1>2
                                    T3{i2,j2}{1,2}{1,x2}{1,2}(z1)=100;
                                end
                                
                                if min1+min2<C(i1,j1)+C(i2,j2)
                                    C(i1,j1)=min1;
                                    C(i2,j2)=min2;
                                else
                                    temp=T3{i2,j2}{1,2}{1,x2};
                                    T3{i2,j2}{1,2}{1,x2}=T3{i1,j1}{1,2}{1,x1};
                                    T3{i1,j1}{1,2}{1,x1}=temp;
                                end
                                end
                            end
                        end
                    end
                end
            end
        end
    end
end
Psum1=0;
for i=1:15
    for j=1:6
        Psum1=Psum1+C(i,j);
    end
end
disp(Psum1);
end

Psum1=0;
for i=1:15
    for j=1:6
        Psum1=Psum1+C(i,j);
    end
end
disp(Psum1);


B2=cell(15,6);
for i=1:15
    for j=1:6
        B2{i,j}=cell(1,2);
        B2{i,j}{1,1}=T2{i,j}{1,1};
        B2{i,j}{1,2}=cell(7,2);
        for k=1:T2{i,j}{1,1}
            B2{i,j}{1,2}{k,1}=T2{i,j}{1,2}{1,k}{1,1};
            B2{i,j}{1,2}{k,2}=T2{i,j}{1,2}{1,k}{1,2};
        end
    end
end

B3=cell(15,6);
for i=1:15
    for j=1:6
        B3{i,j}=cell(1,2);
        B3{i,j}{1,1}=T3{i,j}{1,1};
        B3{i,j}{1,2}=cell(7,2);
        for k=1:T3{i,j}{1,1}
            B3{i,j}{1,2}{k,1}=T3{i,j}{1,2}{1,k}{1,1};
            B3{i,j}{1,2}{k,2}=T3{i,j}{1,2}{1,k}{1,2};
        end
    end
end


disp('end');