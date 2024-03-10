#pragma once

/**
 * @file Display.h
 *
 * @brief
 *
 * @author
 * Contact:
 *
 */

#include <iostream>
#include <Windows.h>  

/**
 * Implementation of Display class
 *
 *
 */
class Frame
{
public:
	int vnFrameWidth;
	int vnFrameHeight;
	int* vaCanvas;

private:
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

public:
	Frame(int const ip_nWitdh, int const ip_nHeight, int* ip_aCanvas);

	Frame();

	void Initialize(int const ip_nWitdh, int const ip_nHeight, int* ip_aCanvas);

	void AddImageToCanvas(int* ip_aImage, int ip_nXPosition, int ip_nYPosition);

	void Draw(int image[], int ip_nFrameWidth, int ip_nFrameHeight, int ip_nXCoordinate, int ip_nYCoordinate);
	void Draw();

	void ToCoordinate(int a, int b);

	void SetColor(int);

};