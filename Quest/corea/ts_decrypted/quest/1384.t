CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1384;
	title = 138402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 100;
			prelnk = "4;";

			CDboTSActWorldPlayScript
			{
				sid = 1384;
				start = 0;
				taid = 1;
				uof = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 5;

			CDboTSRcvSvrEvt
			{
				id = 301;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 252;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActWorldPlayScript
			{
				sid = 1384;
				start = 1;
				taid = 1;
				uof = 1;
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
				conv = 138409;
				ctype = 1;
				idx = 1353102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 138408;
				gtype = 3;
				area = 138401;
				goal = 138404;
				grade = 132203;
				rwd = 100;
				sort = 138405;
				stype = 1;
				taid = 1;
				title = 138402;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 138407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1353102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 54;
				minlvl = 46;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "3;2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 138408;
			gtype = 3;
			oklnk = 2;
			area = 138401;
			goal = 138404;
			sort = 138405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 138402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 138414;
			nextlnk = 254;
			rwdtbl = 138401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1351111;
			}
		}
	}
}

