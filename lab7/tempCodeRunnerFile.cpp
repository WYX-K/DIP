 input = (char *)"..\\images\\LenaWithNoise.pgm";
    image = ReadPNMImage(input);

    output = (char *)"..\\output\\LenaWithNoise_Bandreject.pgm";
    outimage = BandrejectImage(image, 10, 100);