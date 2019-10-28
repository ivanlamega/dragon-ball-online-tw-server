CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 702;
	title = 70202;

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
				conv = 70209;
				ctype = 1;
				idx = 5061202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 70208;
				gtype = 1;
				area = 70201;
				goal = 70204;
				grade = 132203;
				rwd = 100;
				sort = 70205;
				stype = 2;
				taid = 1;
				title = 70202;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 70208;
			gtype = 1;
			oklnk = 2;
			area = 70201;
			goal = 70204;
			sort = 70205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 70202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 70214;
			nextlnk = 254;
			rwdtbl = 70201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4151105;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 70207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5061202;
			}
			CDboTSCheckLvl
			{
				maxlvl = 31;
				minlvl = 23;
			}
			CDboTSCheckClrQst
			{
				and = "701;";
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
			prelnk = "2;";
		}
	}
}

