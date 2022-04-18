#!/usr/bin/octave
function plotBER(filename,plotFlag)
warning('off','all'); # Suppress the warning associated with loading berResult into memory
addpath('/home/kheong/Dropbox/swrc_C/modules/berResult/'); # Add the path for the library of functions for plotting from berResult file
berResult # Load those functions into memory

% Set the filename and filenum parameters
  BERHash            = BERResult_addfileNameNumToHash(struct(),filename);
  BERHash.plotFlag   = plotFlag;
  % Set it up for FER/BER vs SNR plots
  BERHash.xCol       = [2];
  BERHash.xColParm   = {'SNR'};
  BERHash.xColFormat = {'%4.1f'};
  BERHash.yCol       = [11];
  BERHash.yColParm   = {'FER'};
  BERHash.yIndex     = 1;           % The index of the y variable that you want to plot
  BERHash.yColFormat = {'%0.10f'};
  BERHash.zCol       = [3];        % z-parameters create one line on the plot per value of z.
  BERHash.zColParm   = {'N'};
  BERHash.zColFormat = {'%.0f'};
  BERHash.wCol       = [6]; % w-parameters create one new plot per unique combination of w.
  BERHash.wColParm   = {'R'};
  BERHash.wColFormat = {'%.3f'};
  BERHash.uCol       = [8];        % u-col parameters are included in the array. They carry useful information, but are not plotted.
  BERHash.uColParm   = {'#FrErr'};
  BERHash.uColFormat ={'%.0f'};
  BERHash.plotAxes = [0, 9, 1e-6, 1]; % The x and y limits of the axes
  BERHash.semilogFlag= 1;            % 1 means semilog on the y axis. 2 means on the x axis, 3 means on both axes.
  BERHash.legendLoc='northeast';
  BERHash.exclusion  = {'SNR=-0.5','SNR=0.5','SNR=1.5','SNR=2.5','SNR=3.5','SNR=4.5','SNR=5.5','#FrErr<10'};% exclusions are points in the data that we don't want included
  BERHash.extraPoints=[];           % extra points are added to the list before curve fitting.
  BERHash.polyDegree =2;            % fit parabolas to datapoints
  BERHash.xRangeFit  =[];           % The x-range of the data for fitting purposes
  BERHash.xRangePlot =[];           % The x-range of the data for plotting purposes
  BERHash.lineWidth  =1.5;          % Width of the lines on the plots
  BERHash.PDFSize    = '-S500,350'; % Size of the PDF.
  BERHash.colorScheme={[0,0,1],[1,0,0],[0,1,0],[0.9,0,0.9],[0,0.9,0.9],[0.9,0.7,0],[0.1,0.5,0.2],[1,0.5,0],[0,0,0.5],[0.5,0,0],[0,0.5,0],[0.45,0.3,0.45],[0,0.45,0.45]};
  plotBERResult(BERHash);
endfunction
