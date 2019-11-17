package com.epicgames.ue4;

import com.maxrankstudio.jumpswitch.OBBDownloaderService;
import com.maxrankstudio.jumpswitch.DownloaderActivity;


public class DownloadShim
{
	public static OBBDownloaderService DownloaderService;
	public static DownloaderActivity DownloadActivity;
	public static Class<DownloaderActivity> GetDownloaderType() { return DownloaderActivity.class; }
}

