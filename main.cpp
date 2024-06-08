#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <filesystem>

using namespace std;
using namespace cv;
namespace fs = std::filesystem;

string pixelToASCII(int pixel_intensity)
{
  const string ASCII_CHARS = "   ._-=+*!&#%$@";
  string s = string(1, ASCII_CHARS[pixel_intensity * ASCII_CHARS.length() / 256]);
  return s;
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <video_path>" << endl;
    return -1;
  }

  fs::path video_path = fs::absolute(argv[1]);

  VideoCapture cap(video_path.string());

  if (!cap.isOpened())
  {
    cerr << "Error: Could not open the video file." << endl;
    return -1;
  }

  double fps = cap.get(CAP_PROP_FPS);
  cout << "FPS: " << fps << endl;

  int frame_duration_ms = 1000 / fps;

  int width = 250;
  int height = 50;

  int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
  int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);
  cout << "Frame Width: " << frame_width << " Frame Height: " << frame_height << endl;

  height = static_cast<int>((width * frame_height / frame_width) * 0.4194);

  Mat frame, gray_frame, resized_frame;

  while (true)
  {
    cap >> frame;

    if (frame.empty())
      break;

    cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
    resize(gray_frame, resized_frame, Size(width, height), 0, 0, INTER_LINEAR);

    string ascii_frame;
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        ascii_frame += pixelToASCII(resized_frame.at<uchar>(i, j));
      }
      ascii_frame += "\n";
    }

    system("clear");
    cout << ascii_frame;
    this_thread::sleep_for(chrono::milliseconds(frame_duration_ms));
  }

  return 0;
}
