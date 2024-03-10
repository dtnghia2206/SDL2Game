/**
 * @file Display.cpp
 *
 * @brief 
 *
 * @author 
 * Contact:
 *
 */

#include "Frame.h"

Frame::Frame(int const ip_nWitdh, int const ip_nHeight, int* ip_aCanvas)
{
	vnFrameWidth  = ip_nWitdh;
	vnFrameHeight = ip_nHeight;
	vaCanvas      = ip_aCanvas;
}

Frame::Frame()
{
	int a = 0;
	vnFrameWidth = 0;
	vnFrameHeight = 0;
	vaCanvas = &a;
}

void Frame::Initialize(int const ip_nWitdh, int const ip_nHeight, int* ip_aCanvas)
{
	vnFrameWidth = ip_nWitdh;
	vnFrameHeight = ip_nHeight;
	vaCanvas = ip_aCanvas;
}

/** Draw the whole scene with a rectangle.
* @param 
* @param
*/
void Frame::Draw(int image[], int ip_nFrameWidth, int ip_nFrameHeight, int ip_nXCoordinate, int ip_nYCoordinate)
{
	
	for (int i = 0; i < ip_nFrameHeight; i++)
	{
		for (int j = 0; j < ip_nFrameWidth; j++)
		{
			ToCoordinate((ip_nXCoordinate * 2) + (j*2), ip_nYCoordinate + i);

			// Transparent background
			if (!(image[(i * ip_nFrameWidth) + j + 2] == 0))
			{
				SetColor(image[(i * ip_nFrameWidth) + j + 2]);

				std::cout << char(219) << char(219); // █ + █ = ██ square pixel instead of rectangle
			}
		}
		std::cout << std::endl;
	}
}

void Frame::Draw()
{

	for (int i = 0; i < vnFrameHeight; i++)
	{
		for (int j = 0; j < vnFrameWidth; j++)
		{
			ToCoordinate((j * 2), i);

			SetColor(vaCanvas[(i * vnFrameWidth) + j]);

			std::cout << char(219) << char(219); // █ + █ = ██ square pixel instead of rectangle

		}
		std::cout << std::endl;
	}
}

void Frame::AddImageToCanvas(int* ip_aImage, int ip_nInsertPositionX, int ip_nInsertPositionY)
{
	int vnImageWidth   = ip_aImage[0];
	int vnImageHeight  = ip_aImage[1];
	int vnInsertPosition = 0;

	for (int vnImageYPos = 0; vnImageYPos < vnImageHeight; vnImageYPos++)
	{
		for (int vnImageXPos = 0; vnImageXPos < vnImageWidth; vnImageXPos++)
		{
			vnInsertPosition = (ip_nInsertPositionY + vnImageYPos) * vnFrameWidth + ip_nInsertPositionX + vnImageXPos;

			vaCanvas[vnInsertPosition] = ip_aImage[vnImageYPos * vnImageWidth + vnImageXPos + 2];
		}
	}
}


/** Set the color of the printed character on the console.
* @param
* @param
*/
void Frame::ToCoordinate(int vnXCoordinate, int vnYCoordinate)
{
	COORD coord;
	coord.X = vnXCoordinate;
	coord.Y = vnYCoordinate;
	SetConsoleCursorPosition(out, coord);
}

/** 
* @param
* @param
*/
void Frame::SetColor(int y)
{
	SetConsoleTextAttribute(out, y);
}
