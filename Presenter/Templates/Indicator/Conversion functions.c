	#region Conversion functions
        
    string DoubleToStr(double value, int digits)
    {
      return value.ToString("F" + digits);
    }

    Mq4Double NormalizeDouble(double value, int digits)
    {
      return Math.Round(value, digits);
    }

    Mq4Double StrToDouble(string value)
    {
      return double.Parse(value);
    }

    Mq4Double StrToInteger(string value)
    {
      return int.Parse(value);
    }

    string TimeToStr(int value, int mode = TIME_DATE|TIME_MINUTES)
    {
      var formatString = "";
      if ((mode & TIME_DATE) != 0)
        formatString += "yyyy.MM.dd ";
      if ((mode & TIME_SECONDS) != 0)
        formatString += "HH:mm:ss";             
      else if ((mode & TIME_MINUTES) != 0)
        formatString += "HH:mm";      
      formatString = formatString.Trim();

      return Mq4TimeSeries.ToDateTime(value).ToString(formatString);
    }
		
	int StrToTime(string value)
	{
		var dateTime = StrToDateTime(value);
		return Mq4TimeSeries.ToInteger(dateTime);
	}

	private static readonly Regex TimeRegex = new Regex(@@"((?<year>\d+)\.(?<month>\d+)\.(?<day>\d+)){0,1}\s*((?<hour>\d+)\:(?<minute>\d+)){0,1}", RegexOptions.Compiled);
	DateTime StrToDateTime(string value)
	{
		var dateTime = Server.Time.Date;

		var match = TimeRegex.Match(value);
		if (!match.Success)
			return dateTime;		
				
		if (match.Groups["year"].Value != string.Empty)
		{
			dateTime = new DateTime(int.Parse(match.Groups["year"].Value), int.Parse(match.Groups["month"].Value), int.Parse(match.Groups["day"].Value));
		}		
		if (match.Groups["hour"].Value != string.Empty)
			dateTime = dateTime.AddHours(int.Parse(match.Groups["hour"].Value));
		if (match.Groups["minute"].Value != string.Empty)
			dateTime = dateTime.AddMinutes(int.Parse(match.Groups["minute"].Value));

		return dateTime;
	}

	#endregion