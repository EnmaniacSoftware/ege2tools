#include "Application.hpp"

#include <QDebug>

int main(int argc, char *argv[])
{
  try
  {
    ege::Application application(argc, argv);
    return application.exec();
  }
    catch (std::exception& e)
    {
      qCritical() << e.what();
    }

    return -1;
}

