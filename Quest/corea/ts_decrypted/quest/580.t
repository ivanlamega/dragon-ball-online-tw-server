CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 580;
	title = 58002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSBindStone
			{
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 58009;
				ctype = 1;
				idx = 7711101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 58008;
				gtype = 1;
				area = 58001;
				goal = 58004;
				m0fz = "-3915.570068";
				m0widx = 1;
				sort = 58005;
				stype = 2;
				m0fy = "-96.580002";
				grade = 132203;
				m0fx = "5818.250000";
				m0ttip = 58015;
				rwd = 100;
				taid = 1;
				title = 58002;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 58007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 7711101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 10;
				minlvl = 2;
			}
			CDboTSCheckClrQst
			{
				and = "403;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 58008;
			gtype = 1;
			oklnk = 2;
			area = 58001;
			goal = 58004;
			sort = 58005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 58002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 58014;
			nextlnk = 254;
			rwdtbl = 58001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7711101;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

