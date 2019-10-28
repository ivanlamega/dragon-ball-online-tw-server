CNtlTSTrigger
{
	sm = 1;
	sq = 0;
	rq = 0;
	tid = 752;
	title = 75202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 203;
			elnk = 255;
			nextlnk = 254;
			prelnk = "4;";

			CDboTSActObjState
			{
				mstate = 255;
				oidx = 544;
				osh_sh = 255;
				widx = 1;
				osh_uc = 0;
				taid = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "203;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 203;
			prelnk = "9;9;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 1000;
			}
		}
		CDboTSContGAct
		{
			cid = 9;
			elnk = 4;
			nextlnk = 4;
			prelnk = "0;";

			CDboTSActObjWPS
			{
				sid = 752;
				taid = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 9;

			CDboTSCheckProgQuest
			{
				qid = 752;
			}
			CDboTSCheckAttachObj
			{
				objidx = "544;";
				widx = 1;
			}
		}
	}
}

