#include "helpers.h"
#include<math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbGray;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) {

            rgbGray = round( (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/ 3.00);

            image[i][j].rgbtBlue = rgbGray;
            image[i][j].rgbtGreen = rgbGray;
            image[i][j].rgbtRed = rgbGray;

        }
    }
    return;
}

int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
/*{
    int sepiared;
    int sepiagreen;
    int sepiablue;


    for ( int i = 0; i < height; i++)
    {
        for ( int j = 0; j < width; j++)
        {
     int red = image[i][j].rgbtRed;
     int green = image[i][j].rgbtGreen;
     int blue =image[i][j].rgbtBlue;
            sepiared = limit(round(.393 * red + .769 * green + .189 * blue));
            sepiagreen= limit(round(.349 * red + .686 * green + .168 * green));
            sepiablue = limit(round (.272 * red + .534 * green + .131 * blue));

            image[i][j].rgbtBlue = sepiablue;
            image[i][j].rgbtGreen = sepiagreen;
            image[i][j].rgbtRed = sepiared;
        }
    }
    return;
}*/
    {int sepiaBlue;
    int sepiaRed;
    int sepiaGreen;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaBlue = limit(round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue));
            sepiaGreen = limit(round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue));
            sepiaRed = limit(round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue));

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j=0; j<height; j++)
    {
    RGBTRIPLE temp[width];
    for(int i=0; i<width; i++)
    {
        temp[width-1-i] = image[j][i];
    }
    for(int i=0; i<width; i++)
    {
        image[j][i]= temp[i];
    }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // creating a temp array and copying image into it
    RGBTRIPLE copy[height][width];
    for(int i=0; i<height; i++)
    {
    for(int j=0;j<width;j++)
    {
     image[i][j]=copy[i][j];
    }
    }
    //using for loops to select first element in copy array and initializing floats for new values of rgb and counter to check how may time change occured
    for(int i=0; i<height; i++)
    {
    for(int j=0;j<width;j++)
    {
        float counter = 0;
        float averagered = 0;
        float averagegreen = 0 ;
        float averageblue = 0 ;
        //now using for loops to go to the left of the chosen element and moving till the box on the immidiate right of it
  for(int x = -1; x<2; x++)
  {
    // adding zero if we move out of the image
    if(j+x<0 && j+x > width)
    {
        averagered += 0;
        averageblue += 0;
        averagegreen += 0;
    }
    else
    {
        //moving from the block on top of the chosen block till the one below it
       for(int k = -1; k<2; k++ )
    {
        //checking if we have moved out of the image
        if (i+k<0 && i+k>height)
    {
            averagered += 0;
            averageblue += 0;
            averagegreen += 0;
    }

        else
        {
//adding the values of rgb in each block and adding 1 to counter each time
            averagered += copy[i+k][j+x].rgbtRed;
            averageblue += copy[i+k][j+x].rgbtBlue;
            averagegreen += copy[i+k][j+x].rgbtGreen;
            counter++;
        }
    }
    }
  }
  //copying the average to the oringinal image
  image[i][j].rgbtRed = averagered/counter;
  image[i][j].rgbtGreen = averagegreen/counter;
  image[i][j].rgbtBlue =averageblue/counter;
    }
    }
    return;
}
