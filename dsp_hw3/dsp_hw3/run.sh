#!/bin/bash

source path.sh;

cd Submit_Files;mkdir testdata;cd ..

perl separator_big5.pl corpus.txt > corpus_seg.txt
perl separator_big5.pl /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/testdata/example.txt > /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/Submit_Files/testdata/example.txt
perl separator_big5.pl /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/testdata/1.txt > /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/Submit_Files/testdata/1.txt
perl separator_big5.pl /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/testdata/2.txt > /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/Submit_Files/testdata/2.txt
perl separator_big5.pl /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/testdata/3.txt > /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/Submit_Files/testdata/3.txt
perl separator_big5.pl /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/testdata/4.txt > /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/Submit_Files/testdata/4.txt
perl separator_big5.pl /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/testdata/5.txt > /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/Submit_Files/testdata/5.txt
perl separator_big5.pl /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/testdata/6.txt > /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/Submit_Files/testdata/6.txt
perl separator_big5.pl /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/testdata/7.txt > /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/Submit_Files/testdata/7.txt
perl separator_big5.pl /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/testdata/8.txt > /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/Submit_Files/testdata/8.txt
perl separator_big5.pl /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/testdata/9.txt > /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/Submit_Files/testdata/9.txt
perl separator_big5.pl /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/testdata/10.txt > /Users/Plabo/OneDrive/Course/DigitalSpeech/DSP_Hw/dsp_hw3/dsp_hw3/Submit_Files/testdata/10.txt
echo Perl_DONE!

ngram-count -text corpus_seg.txt -write lm.cnt -order 2
ngram-count -read lm.cnt -lm bigram.lm -unk -order 2
echo ngram-count_DONE!

cd Submit_Files;make map; cd ..
echo MakeMap_DONE!