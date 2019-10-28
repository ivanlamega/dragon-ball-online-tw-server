CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1545;
	title = 154502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 154507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4371203;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 154514;
			nextlnk = 101;
			rwdtbl = 154501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4371203;
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
				conv = 154509;
				ctype = 1;
				idx = 4371203;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 154508;
				m1fx = "119.000000";
				area = 154501;
				goal = 154504;
				m0fz = "-456.000000";
				m0widx = 9;
				m1fy = "0.000000";
				m1ttip = 154516;
				sort = 154505;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-437.000000";
				grade = 132203;
				m0fx = "113.000000";
				m0ttip = 154515;
				m1widx = 9;
				rwd = 100;
				taid = 1;
				title = 154502;
				gtype = 4;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 14;
				eitype = 0;
				idx0 = 7211107;
				cnt0 = 14;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 3501112;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 154508;
			gtype = 4;
			oklnk = 2;
			area = 154501;
			goal = 154504;
			sort = 154505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 154502;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

