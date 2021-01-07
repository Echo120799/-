
%% Homomorphic Filtering
% 
% $$ \ln(I(x,y)) = \ln(L(x,y)\ R(x,y))$$

%%

I = imread('Fig0462_PET_image.tif');
figure(1)
imshow(I),title('origin')
%%
%  Let's use homomorphic filtering to correct this non-uniform illumination.

%% 
% The first step is to convert the input image to the log domain. Before
% that we will also convert the image to floating-point type.
[M, N] = size(I);
I = im2double(I);

%% add 1 to pixels to remove 0 values which would result in undefined log values
I = log(1 + I);


%% 
% And create the high-pass filter...
lowg=0.25;
higg=2;
coeff=1;
sigma = 80;
[X, Y] = meshgrid(1:N,1:M);
centerX = ceil(N/2); 
centerY = ceil(M/2); 
gaussianNumerator = (X - centerX).^2 + (Y - centerY).^2;
H = coeff*exp(-gaussianNumerator./(sigma.^2));
H = (higg-lowg)*(1 - H)+lowg; 

%% 
% We can rearrange the filter in the _uncentered_ format using |fftshift|.

H = fftshift(H);

%% 
% Next, we high-pass filter the log-transformed image in the frequency
% domain. 

If = fft2(I, M, N);
Iout = real(ifft2(H.*If));


%% 
% The last step is to apply the exponential function to invert the
% log-transform and get the homomorphic filtered image. 
Ihmf = exp(Iout) - 1;

%%
% Let's look at the homomorphic-filtered image.

figure(2)
imshow(Ihmf,[]),title('result');
result = mat2gray(Ihmf);
% save intensities using imwrite
imwrite(result, 'filtered_image.png');
figure(3)
imshowpair(I, Ihmf, 'montage')
%%
