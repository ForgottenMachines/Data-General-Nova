--
-- Database: `phptutorial`
--

--
-- Table structure for table `studentinfo`
--

CREATE TABLE IF NOT EXISTS `studentinfo` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Name` varchar(80) NOT NULL,
  `Roll` int(5) NOT NULL,
  `Position` int(2) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=10 ;

--
-- Dumping data for table `studentinfo`
--

INSERT INTO `studentinfo` (`Id`, `Name`, `Roll`, `Position`) VALUES
(5, 'Vivek Moyal', 5, 4),
(6, 'Vikas Moyal', 8, 2),
(7, 'Divya Moyal', 10, 5),
(8, 'Khusbu Moyal', 9, 3),
(9, 'Savya Moyal', 10, 1);