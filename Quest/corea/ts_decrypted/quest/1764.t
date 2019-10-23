CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1764;
	title = 176402;

	CNtlTSGroup
	{
		gid = 0;

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
				eitype = 1;
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
			stdiag = 176407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1651101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1763;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 176409;
				ctype = 1;
				idx = 1651101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 176408;
				m1fx = "-408.000000";
				area = 176401;
				goal = 176404;
				m0fz = "197.000000";
				m0widx = 10;
				m1fy = "0.000000";
				m1ttip = 176416;
				sort = 176405;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-135.000000";
				grade = 132203;
				m0fx = "-238.000000";
				m0ttip = 176415;
				m1widx = 10;
				rwd = 100;
				taid = 1;
				title = 176402;
				gtype = 4;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 1;
				idx0 = 993;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 994;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 176414;
			nextlnk = 101;
			rwdtbl = 176401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSCheckSToCEvt
			{
				itype = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 1651101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 176408;
			gtype = 4;
			oklnk = 2;
			area = 176401;
			goal = 176404;
			sort = 176405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 176402;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				taid = 1;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 176407;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

