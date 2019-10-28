CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1762;
	title = 176202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 176209;
				ctype = 1;
				idx = 6311102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 176208;
				gtype = 1;
				area = 176201;
				goal = 176204;
				grade = 132203;
				rwd = 100;
				sort = 176205;
				stype = 2;
				taid = 1;
				title = 176202;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 176208;
			gtype = 1;
			oklnk = 2;
			area = 176201;
			goal = 176204;
			sort = 176205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 176202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 176214;
			nextlnk = 254;
			rwdtbl = 176201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1651101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 176207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6311102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1726;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

