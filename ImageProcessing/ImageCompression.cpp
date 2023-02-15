#include <iostream>
#include <string>
#include <chrono>
#include <boost/filesystem.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

struct HumanReadable {
	std::uintmax_t size{};
private: friend
	std::ostream& operator<<(std::ostream& os, HumanReadable hr) {
	int i{};
	double mantissa = hr.size;
	for (; mantissa >= 1024.; mantissa /= 1024., ++i) {}
	mantissa = std::ceil(mantissa * 10.) / 10.;
	os << mantissa << "BKMGTPE"[i];
	return i == 0 ? os : os << "B (" << hr.size << ')';
}
};

void CompressMatAndMeasureTime(cv::Mat& mat, std::string outputFileName)
{
	std::vector<int> param(2);
	param[0] = cv::IMWRITE_JPEG_QUALITY;
	param[1] = 90;

	auto rows = mat.rows;
	auto cols = mat.cols;

	std::cout << "Height (rows) x Width (Cols): " << rows << " x " << cols << std::endl;

	// Write to jpg to file
	std::string outputFile = "A:/" + outputFileName + ".jpg";
	auto start = std::chrono::steady_clock::now();
	cv::imwrite(outputFile, mat, param);
	auto end = std::chrono::steady_clock::now();

	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	// Get file size 
	auto filePath = boost::filesystem::path(outputFile);
	std::cout << "Time taken for conversion jpg to file: " << ms.count() << " ms" << " Size: " << HumanReadable(boost::filesystem::file_size(filePath)) << std::endl;

	// Encode in memory (jpg)
	std::vector<uchar> bufferJpg;
	start = std::chrono::steady_clock::now();
	cv::imencode(".jpg", mat, bufferJpg, param);
	end = std::chrono::steady_clock::now();

	ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time taken for conversion jpg to memory: " << ms.count() << " ms" << std::endl;

	// Write to png to file
	outputFile = "A:/" + outputFileName + ".png";
	start = std::chrono::steady_clock::now();
	cv::imwrite(outputFile, mat, param);
	end = std::chrono::steady_clock::now();

	ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	// Get file size 
	filePath = boost::filesystem::path(outputFile);
	std::cout << "Time taken for conversion png to file: " << ms.count() << " ms" << " Size: " << HumanReadable(boost::filesystem::file_size(filePath)) << std::endl;

	// Encode in memory (png)
	std::vector<uchar> bufferPng;
	start = std::chrono::steady_clock::now();
	cv::imencode(".png", mat, bufferPng, param);
	end = std::chrono::steady_clock::now();

	ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time taken for conversion png to memory: " << ms.count() << " ms" << std::endl;
}

void ReadImageFromFileAndProcess(std::string fileName)
{
	cv::Mat imgOriginal = cv::imread(fileName, 0);

	auto fileNameWithoutExtension = boost::filesystem::path(fileName).stem().string();
	std::string heading1(100, '=');
	std::cout << heading1 << std::endl;
	std::cout << "Processing ... " << fileName << std::endl;

	// Compress and measure
	CompressMatAndMeasureTime(imgOriginal, fileNameWithoutExtension + "_original");

	std::string heading2(100, '-');
	std::cout << heading2 << std::endl;

	// Resize 1/2
	std::cout << " Resizing 1/2" << std::endl;
	cv::Mat resized1_2;
	auto start = std::chrono::steady_clock::now();
	cv::resize(imgOriginal, resized1_2, cv::Size(imgOriginal.cols / 2, imgOriginal.rows / 2));
	auto end = std::chrono::steady_clock::now();

	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time taken for resizing matrix: " << ms.count() << " ms" << std::endl;

	// Compress and measure
	CompressMatAndMeasureTime(resized1_2, fileNameWithoutExtension + "_resized2");
	std::cout << heading2 << std::endl;

	// Resize 1/4
	std::cout << " Resizing 1/4" << std::endl;
	cv::Mat resized1_4;
	start = std::chrono::steady_clock::now();
	cv::resize(imgOriginal, resized1_4, cv::Size(imgOriginal.cols / 4, imgOriginal.rows / 4));
	end = std::chrono::steady_clock::now();

	ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time taken for resizing matrix: " << ms.count() << " ms" << std::endl;

	// Compress and measure
	CompressMatAndMeasureTime(resized1_4, fileNameWithoutExtension + "_resized4");
	std::cout << heading2 << std::endl;
}

int main()
{
	ReadImageFromFileAndProcess("sample_5MP.bmp");
	ReadImageFromFileAndProcess("sample_50MP.bmp");

	std::cin.get();
}
